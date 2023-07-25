#include "DateEvents.h"

//Добавление события для определенной даты
void DatesEvents::AddDateEvent(Date& _date, string event)
{
	int resultAdd = 0; //словарь без изменения
	auto newDate = DateEvents.find(_date);

	if (newDate == DateEvents.end()) //нет такой даты
	{
		DateEvents[_date].push_back(event); //добавление новой даты и события
		resultAdd = 1; //добавлена дата
	}
	else //уже есть дата
	{
		auto newEvent = find(DateEvents[_date].begin(), DateEvents[_date].end(), event);
		if (newEvent == DateEvents[_date].end())
		{
			DateEvents[_date].push_back(event); //добавление нового события
			resultAdd = 2; //добавлено событие
		}
	}

	if (path != "") //добавление в файл
	{
		switch (resultAdd)
		{
		case 0:
			cout << "Event alredy added" << endl;
			return;
		case 1:
			cout << "Date added: ";
			PrintSliceDate(_date.GetDay(),false);
			PrintSliceDate(_date.GetMonth(), false);
			PrintSliceDate(_date.GetYear(), true);
			cout << "with event: " << event << endl;
			break;
		case 2:
			cout << "Event added: " << event << " for date: ";
			PrintSliceDate(_date.GetDay(), false);
			PrintSliceDate(_date.GetMonth(), false);
			PrintSliceDate(_date.GetYear(), true);
			cout << endl;
			break;
		}

		UpdateTextFile(); //обновление текстового файла
	}
}

//Удаление одного события у выбранной даты
void DatesEvents::DeletEventDate(Date& _date, string& event)
{
	//Поиск и удаление события для конкретной даты
	auto delEvent = find(DateEvents[_date].begin(), DateEvents[_date].end(), event);
	if (delEvent != DateEvents[_date].end())
	{
		DateEvents[_date].erase(delEvent);
		cout << "Event deleted: " << event << " from date: ";
		PrintSliceDate(_date.GetDay(), false);
		PrintSliceDate(_date.GetMonth(), false);
		PrintSliceDate(_date.GetYear(), true);
		cout << endl;

		if (DateEvents[_date].empty())
		{
			DateEvents.erase(_date); //удаление объекта data, если у него нет событий
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

	//обновление текстового файла
	UpdateTextFile();
}

//Удаление выбранной даты вместе со всеми событиями
void DatesEvents::DeleteDate(Date& _date)
{
	//Поиск и удаление даты из словаря
	auto delDate{ find_if(DateEvents.begin(), DateEvents.end(), [_date](const pair<Date, vector<string>>& dEv)
	{return dEv.first == _date; }) };

	if (delDate != DateEvents.end())
	{
		DateEvents.erase(delDate);
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

	//обновление текстового файла
	UpdateTextFile();
}

//Поиск даты и вывод всех её событий
void DatesEvents::FindDateEvents(const Date& _date)
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
		//Перед выводом событий их нужно отсортировать
		sort(FindDate->second.begin(), FindDate->second.end());

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

//Загрузка данных из файла в словарь
void DatesEvents::LoadDataFileInMap()
{
	ifstream input(path);
	if (input)
	{
		string line;
		string path = ""; //пустой путь, чтобы не переписывать файл
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
			AddDateEvent(date1, _event1); //добавление дат и их событий из файла
		}
	}
}

//Обновить порядок дат и событий файла в соответствии со словарем
void DatesEvents::UpdateTextFile()
{
	ofstream output;
	output.open(path); //перезапись файла
	if (output.is_open())
	{
		for (auto cur_data : DateEvents)
		{
			for (auto cur_event : cur_data.second)
			{
				output << cur_event << " ";
				WriteFileSliceDate(cur_data.first.GetDay(), output);
				WriteFileSliceDate(cur_data.first.GetMonth(), output);
				WriteFileSliceDate(cur_data.first.GetYear(), output);
				output << endl;
			}
		}
	}
	output.close();
}

void DatesEvents::ReadFileInConsole()
{
	ifstream input(path);
	if (input)
	{
		string line;
		string event, day, month, year;
		while (getline(input, line))
		{
			istringstream iss(line); //поток для разбиения строки файла
			iss >> event;
			iss >> day;
			iss >> month;
			iss >> year;
			cout << event << " " << day << "." << month << "." << year << endl;
		}
	}
}

void DatesEvents::PrintSliceDate(uint16_t slice_date, bool end)
{
	char point = '.';
	if (end) { point = ' '; }

	if (slice_date < 10) { cout << "0" << slice_date << point; }
	else { cout << slice_date << point; }
}

void DatesEvents::WriteFileSliceDate(uint16_t slice_date, ofstream& ofs)
{
	if (slice_date < 10) { ofs << "0" << slice_date << " "; }
	else { ofs << slice_date << " "; }
}