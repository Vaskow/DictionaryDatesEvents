#include "DateEvents.h"

//���������� ������� ��� ������������ ����
void DatesEvents::AddDateEvent(Date& _date, string event, string path)
{
	int resultAdd = 0; //������� ��� ���������
	auto newDate = DateEvents.find(_date);

	if (newDate == DateEvents.end()) //��� ����� ����
	{
		DateEvents[_date].push_back(event); //���������� ����� ���� � �������
		resultAdd = 1; //��������� ����
	}
	else //��� ���� ����
	{
		auto newEvent = find(DateEvents[_date].begin(), DateEvents[_date].end(), event);
		if (newEvent == DateEvents[_date].end())
		{
			DateEvents[_date].push_back(event); //���������� ������ �������
			resultAdd = 2; //��������� �������
		}
	}

	if (path != "") //���������� � ���� �� ���������
	{
		switch (resultAdd)
		{
		case 0:
			cout << "Event alredy added" << endl;
			return;
		case 1:
			//cout << "Date added: " << _date.GetDay() << "." << _date.GetMonth() << "." << _date.GetYear() <<
			//	" with event: " << event << endl;
			cout << "Date added: ";
			PrintSliceDate(_date.GetDay(),false);
			PrintSliceDate(_date.GetMonth(), false);
			PrintSliceDate(_date.GetYear(), true);
			cout << "with event: " << event << endl;
			break;
		case 2:
			//cout << "Event added: " << event << " for date: " << _date.GetDay() << "." <<
			//	_date.GetMonth() << "." << _date.GetYear() << endl;
			cout << "Event added: " << event << " for date: ";
			PrintSliceDate(_date.GetDay(), false);
			PrintSliceDate(_date.GetMonth(), false);
			PrintSliceDate(_date.GetYear(), true);
			cout << endl;
			break;
		}

		UpdateTextFile(path); //���������� ���������� �����
	}
}

//�������� ������ ������� � ��������� ����
void DatesEvents::DeletEventDate(Date& _date, string& event, string path)
{
	//����� � �������� ������� ��� ���������� ����
	auto delEvent = find(DateEvents[_date].begin(), DateEvents[_date].end(), event);
	if (delEvent != DateEvents[_date].end())
	{
		DateEvents[_date].erase(delEvent);
		//cout << "Event deleted: " << event << " from date: " << _date.GetDay() << "." <<
		//	_date.GetMonth() << "." << _date.GetYear() << endl;
		cout << "Event deleted: " << event << " from date: ";
		PrintSliceDate(_date.GetDay(), false);
		PrintSliceDate(_date.GetMonth(), false);
		PrintSliceDate(_date.GetYear(), true);
		cout << endl;
		if (DateEvents[_date].empty())
		{
			DateEvents.erase(_date); //�������� ������� data, ���� � ���� ��� �������
			//cout << "Date deleted: " << _date.GetDay() << "." << _date.GetMonth() << "." << _date.GetYear() << endl;
			cout << "Date deleted: ";
			PrintSliceDate(_date.GetDay(), false);
			PrintSliceDate(_date.GetMonth(), false);
			PrintSliceDate(_date.GetYear(), true);
			cout << endl;
		}
	}
	else
	{
		cout << "Date not found" << endl;
		return;
	}

	//���������� ���������� �����
	UpdateTextFile(path);
}

//�������� ��������� ���� ������ �� ����� ���������
void DatesEvents::DeleteDate(Date& _date, string path)
{
	//����� � �������� ���� �� �������
	auto delDate{ find_if(DateEvents.begin(), DateEvents.end(), [_date](const pair<Date, vector<string>>& dEv)
	{return dEv.first == _date; }) };

	if (delDate != DateEvents.end())
	{
		DateEvents.erase(delDate);
		//cout << "Date deleted: " << _date.GetDay() << "." << _date.GetMonth() << "." << _date.GetYear() << endl;
		cout << "Date deleted: ";
		PrintSliceDate(_date.GetDay(), false);
		PrintSliceDate(_date.GetMonth(), false);
		PrintSliceDate(_date.GetYear(), true);
		cout << endl;
	}
	else
	{
		cout << "Date not found" << endl;
		return;
	}

	//���������� ���������� �����
	UpdateTextFile(path);
}

//����� ���� � ����� ���� � �������
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
		//����� ������� ������� �� ����� �������������
		sort(FindDate->second.begin(), FindDate->second.end());

		//cout << "Find Date = " << FindDate->first.GetDay() << "." <<
		//	FindDate->first.GetMonth() << "." << FindDate->first.GetYear() << endl;
		cout << "Find Date = ";
		PrintSliceDate(FindDate->first.GetDay(), false);
		PrintSliceDate(FindDate->first.GetMonth(), false);
		PrintSliceDate(FindDate->first.GetYear(), true);
		cout << endl;
		cout << "Events: " << endl;
		for (string strEv : FindDate->second)
		{
			cout << " " << strEv << endl;
		}

	}

}

//�������� ������ �� ����� � �������
void DatesEvents::LoadDataFileInMap(const string& path)
{
	ifstream input(path);
	if (input)
	{
		string line;
		string path = ""; //������ ����, ����� �� ������������ ����
		while (getline(input, line))
		{
			string _event1;
			int year = 0, month = 0, day = 0;

			istringstream iss(line);
			iss >> _event1;
			iss >> day;
			iss >> month;
			iss >> year;
			Date date1(day, month, year);
			AddDateEvent(date1, _event1, path); //���������� ��� � �� ������� �� �����
		}
	}
}

//�������� ������� ��� � ������� ����� � ������������ �� ��������
void DatesEvents::UpdateTextFile(const string& path)
{
	ofstream output;
	output.open(path); //���������� �����
	if (output.is_open())
	{
		for (auto cur_data : DateEvents)
		{
			for (auto cur_event : cur_data.second)
			{
				//output << cur_event << " " << cur_data.first.GetDay() << " " << cur_data.first.GetMonth() << " " << cur_data.first.GetYear() << endl;
				output << cur_event << " ";
				//if (cur_data.first.GetDay() < 10) { output << "0" << cur_data.first.GetDay() << " "; }
				//else { output << cur_data.first.GetDay() << " "; }
				//if (cur_data.first.GetMonth() < 10) { output << "0" << cur_data.first.GetMonth() << " "; }
				//else { output << cur_data.first.GetMonth() << " "; }
				//if (cur_data.first.GetYear() < 10) { output << "0" << cur_data.first.GetYear() << endl; }
				//else { output << cur_data.first.GetYear() << endl; }
				WriteFileSliceDate(cur_data.first.GetDay(), output);
				WriteFileSliceDate(cur_data.first.GetMonth(), output);
				WriteFileSliceDate(cur_data.first.GetYear(), output);
				output << endl;
			}
		}
	}
	output.close();
}

void ReadFileInConsole(const string& path)
{
	ifstream input(path);
	if (input)
	{
		string line;
		string event, day, month, year;
		while (getline(input, line))
		{
			istringstream iss(line); //����� ��� ��������� ������ �����
			iss >> event;
			iss >> day;
			iss >> month;
			iss >> year;
			cout << event << " " << day << "." << month << "." << year << endl;
			//if (day < "10") { cout << "d1 " << endl; }
			//else { cout << "d2 = " << day << endl; }
		}
	}
}

