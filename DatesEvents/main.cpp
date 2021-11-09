#include "DateEvents.h"


void ReadFileInConsole(const string& path)
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


int main()
{
	setlocale(LC_ALL, "ru");
	
	// Поток для работы с файлом
	const string path = "Date_Base1.txt";
	ofstream output;
	output.open(path, ios::app); //std::ios::app позволяет дописывать, а не переписывать

	// Массив дат и их событий
	DatesEvents datesEvents;

	datesEvents.LoadDataFileInMap(path); //Считывание данных из файла
	

	cout << "Доступные функции (формат даты: день.месяц.год): " << endl <<
		" Для добавления события ввести: Add Дата Событие" << endl <<
		" Для удаления события ввести: Del Дата Событие" << endl <<
		" Для удаления всех событий за конкретную дату ввести: Del Дата" << endl <<
		" Для поиска событий за конкретную дату ввести: Find Дата" << endl <<
		" Для печати всех событий за все даты ввести: Print" << endl <<
		" Для выхода из программы ввести: Exit" << endl;

	bool exit = false;
	while (!exit)
	{
		string cmd;
		cout << endl;
		cout << "Введите команду: " << endl;
		getline(cin, cmd);

		
		if (cmd == "" || cmd == " ")
		{
			continue;
		}
		else if (cmd == "Exit" || cmd == "exit")
		{
			exit = true;
			continue;
		}
		else if (cmd == "Print")
		{
			ReadFileInConsole(path);
			continue;
		}
		
		string typeCmd, dateCmd, eventCmd;
		int day = 0, month = 0, year = 0;

		istringstream iss(cmd); //поток для разбиения команды
		iss >> typeCmd;
		iss >> dateCmd;
		iss >> eventCmd;

		if (typeCmd != "Add" && typeCmd != "Del" && typeCmd != "Find")
		{
			cout << "Unknown command" << endl;
		}

		stringstream ss1(dateCmd); //поток для разделения даты на составляющие
		vector <string> dateSplit;
		string numDate;
		while (getline(ss1, numDate, '.'))
		{
			dateSplit.push_back(numDate);
		}
		day = stoi(dateSplit[0]);
		month = stoi(dateSplit[1]);
		year = stoi(dateSplit[2]);

		//cout << "Test: " << typeCmd << " " << day << " " << month << " " << year << " " << eventCmd << endl;
		cout << endl;

		Date date1 = { Day(day), Month(month), Year(year) };

		if (typeCmd == "Add")
		{
			datesEvents.AddDateEvent(date1, eventCmd, path);
		}
		else if (typeCmd == "Del" && eventCmd != "")
		{
			datesEvents.DeletEventDate(date1, eventCmd, path);
		}
		else if (typeCmd == "Del" && eventCmd == "")
		{
			datesEvents.DeleteDate(date1, path);
		}
		else if (typeCmd == "Find")
		{
			datesEvents.findDateEvents(date1);
		}
	}

	output.close();


}
