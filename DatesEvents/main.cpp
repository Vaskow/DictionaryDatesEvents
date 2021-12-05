#include "DateEvents.h"

int main()
{
	setlocale(LC_ALL, "ru");

	// Поток для работы с файлом
	const string path = "Date_Base1.txt";
	ofstream output;
	output.open(path, ios::app); 

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

		istringstream iss(cmd); //поток для разбиения команды
		iss >> typeCmd;
		iss >> dateCmd;
		iss >> eventCmd;

		if (typeCmd != "Add" && typeCmd != "Del" && typeCmd != "Find")
		{
			cout << "Unknown command" << endl;
			continue;
		}

		if (typeCmd == "Add" && (eventCmd == "" || eventCmd == " "))
		{
			cout << "Введено пустое событие" << endl;
			continue;
		}
		

		int startSubStr = 0;
		int endSubStr = 0;
		int indArr = 0;
		array<int, 3> arrDate{0};
		for (int i = 0; i < dateCmd.size(); ++i)
		{
			if (dateCmd[i] == '.')
			{
				endSubStr = i;
				arrDate.at(indArr) = stoi(dateCmd.substr(startSubStr, endSubStr));
				startSubStr = i+1;
				indArr++;
			}
			if (indArr == 2)
			{
				arrDate.at(indArr) = stoi(dateCmd.substr(startSubStr, string::npos));
				break;
			}
		}


		cout << endl;

		bool goodDate = VerificDate(arrDate[0], arrDate[1], arrDate[2]);

		if (goodDate == false)
		{
			cout << "Введите правильную дату" << endl;
			continue;
		}

		Date date(arrDate[0], arrDate[1], arrDate[2]);

		if (typeCmd == "Add")
		{
			datesEvents.AddDateEvent(date, eventCmd, path);
		}
		else if (typeCmd == "Del" && eventCmd != "")
		{
			datesEvents.DeletEventDate(date, eventCmd, path);
		}
		else if (typeCmd == "Del" && eventCmd == "")
		{
			datesEvents.DeleteDate(date, path);
		}
		else if (typeCmd == "Find")
		{
			datesEvents.findDateEvents(date);
		}
	}

	output.close();

}
