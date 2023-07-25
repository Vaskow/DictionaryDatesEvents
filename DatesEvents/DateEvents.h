#include "Date.h"

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <algorithm> 
#include <map>
#include <sstream> 

using namespace std;

class DatesEvents
{
public:

	DatesEvents() : path{"Date_Base1.txt"}
	{
		LoadDataFileInMap();
	}

	DatesEvents(const string& _path) : path{_path}
	{
		LoadDataFileInMap();
	}

	//Добавление события для определенной даты
	void AddDateEvent(Date& _date, string event);
	//Удаление одного события у выбранной даты
	void DeletEventDate(Date& _date, string& event);
	//Удаление выбранной даты вместе со всеми событиями
	void DeleteDate(Date& _date);
	//Поиск даты и вывод всех её событий (заранее отсортировыванных)
	void FindDateEvents(const Date& _date);
	//Чтение файла событий и вывод данных на консоль
	void ReadFileInConsole();

private:

	//Обновить порядок дат и событий файла в соответствии со словарем
	void UpdateTextFile();
	//Загрузка данных из файла в словарь
	void LoadDataFileInMap();
	//Печать фрагмента части даты на консоль
	void PrintSliceDate(uint16_t slice_date, bool end);
	//Запись фрагмента части даты в файл
	void WriteFileSliceDate(uint16_t slice_date, ofstream& ofs);

	map<Date, vector<string>> DateEvents;
	const string path;
};