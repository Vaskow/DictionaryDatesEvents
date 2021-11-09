#include "DateEvents.h"

//Äîáàâëåíèå ñîáûòèÿ äëÿ îïðåäåëåííîé äàòû
void DatesEvents::AddDateEvent(Date&_date, string event, string path)
{
	int resultAdd = 0; //ñëîâàðü áåç èçìåíåíèÿ
	auto newDate = DateEvents.find(_date);

	if (newDate == DateEvents.end()) //íåò òàêîé äàòû
	{
		DateEvents[_date].push_back(event); //äîáàâëåíèå íîâîé äàòû è ñîáûòèÿ
		resultAdd = 1; //äîáàâëåíà äàòà
	}
	else //óæå åñòü äàòà
	{
		auto newEvent = find(DateEvents[_date].begin(), DateEvents[_date].end(), event);
		if (newEvent == DateEvents[_date].end())
		{
			DateEvents[_date].push_back(event); //äîáàâëåíèå íîâîãî ñîáûòèÿ
			resultAdd = 2; //äîáàâëåíî ñîáûòèå
		}
	}

	if (path != "") //äîáàâëåíèå â ôàéë íå òðåáóåòñÿ
	{
		switch (resultAdd)
		{
		case 0: 
			cout << "Event alredy added" << endl;
			return;
		case 1: 
			cout << "Date added: " << _date.day << "." << _date.month << "." << _date.year <<
				" with event: " << event << endl;
			break;
		case 2: 
			cout << "Event added: " << event  << " for date: " << _date.day << "." << 
				_date.month << "." << _date.year << endl;
			break;
		}

		UpdateTextFile(path); //îáíîâëåíèå òåêñòîâîãî ôàéëà
	}
}

//Óäàëåíèå îäíîãî ñîáûòèÿ ó âûáðàííîé äàòû
void DatesEvents::DeletEventDate(Date&_date, string& event, string path)
{
	//Ïîèñê è óäàëåíèå ñîáûòèÿ äëÿ êîíêðåòíîé äàòû
	auto delEvent = find(DateEvents[_date].begin(), DateEvents[_date].end(), event);
	if (delEvent != DateEvents[_date].end())
	{
		DateEvents[_date].erase(delEvent);
		cout << "Event deleted: " << event << " from date: " << _date.day << "." <<
			_date.month << "." << _date.year << endl;
		if (DateEvents[_date].empty())
		{
			DateEvents.erase(_date); //óäàëåíèå îáúåêòà data, åñëè ó íåãî íåò ñîáûòèé
			cout << "Date deleted: " << _date.day << "." << _date.month << "." << _date.year << endl;
		}
	}
	else
	{
		cout << "Date not found" << endl;
		return;
	}

	//îáíîâëåíèå òåêñòîâîãî ôàéëà
	UpdateTextFile(path);
}

//Óäàëåíèå âûáðàííîé äàòû âìåñòå ñî âñåìè ñîáûòèÿìè
void DatesEvents::DeleteDate(Date&_date, string path)
{
	//Ïîèñê è óäàëåíèå äàòû èç ñëîâàðÿ
	auto delDate{ find_if(DateEvents.begin(), DateEvents.end(), [_date](const pair<Date, vector<string>>& dEv)
	{return dEv.first == _date; }) };

	if (delDate != DateEvents.end())
	{
		DateEvents.erase(delDate); 
		cout << "Date deleted: " << _date.day << "." << _date.month << "." << _date.year << endl;
	}
	else
	{
		cout << "Date not found" << endl;
		return;
	}

	//îáíîâëåíèå òåêñòîâîãî ôàéëà
	UpdateTextFile(path);
}

//Ïîèñê äàòû è âûâîä âñåõ å¸ ñîáûòèé
void DatesEvents::findDateEvents(const Date& _date)
{
	auto FindDate{ find_if(DateEvents.begin(), DateEvents.end(),
		[_date](const pair<Date, vector<string>>& dEv)
		{return dEv.first == _date; }) };

	if (FindDate == DateEvents.end())
	{
		cout << "Date not found" << endl;
	}
	else
	{
		//Ïåðåä âûâîäîì ñîáûòèé èõ íóæíî îòñîðòèðîâàòü
		sort(FindDate->second.begin(), FindDate->second.end());

		cout << "Find Date = " << FindDate->first.day << "." <<
			FindDate->first.month << "." << FindDate->first.year << endl;
		cout << "Events: " << endl;
		for (string strEv : FindDate->second)
		{
			cout << " " << strEv << endl;
		}

	}

}

//Çàãðóçêà äàííûõ èç ôàéëà â ñëîâàðü
void DatesEvents::LoadDataFileInMap(const string& path)
{
	ifstream input(path);
	if (input)
	{
		string line;
		string path = ""; //ïóñòîé ïóòü, ÷òîáû íå ïåðåïèñûâàòü ôàéë
		while (getline(input, line))
		{
			string _event1;
			int year = 0, month = 0, day = 0;

			istringstream iss(line);
			iss >> _event1;
			iss >> day;
			iss >> month;
			iss >> year;
			Date date1 = { Day(day), Month(month), Year(year) };
			AddDateEvent(date1, _event1, path); //äîáàâëåíèå äàò è èõ ñîáûòèé èç ôàéëà
		}
	}
}

//Îáíîâèòü ïîðÿäîê äàò è ñîáûòèé ôàéëà â ñîîòâåòñòâèè ñî ñëîâàðåì
void DatesEvents::UpdateTextFile(const string& path)
{
	ofstream output;
	output.open(path); //ïåðåçàïèñü ôàéëà
	if (output.is_open())
	{
		for (auto cur_data : DateEvents)
		{
			for (auto cur_event : cur_data.second)
			{
				output << cur_event << " " << cur_data.first.day << " " << cur_data.first.month << " " << cur_data.first.year << endl;
			}
		}
	}
	output.close();
}
