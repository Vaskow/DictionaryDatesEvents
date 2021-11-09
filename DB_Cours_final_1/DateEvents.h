#include "Date.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> 
#include <map>
#include <sstream> //stream string
using namespace std;

#pragma once


class DatesEvents
{
public:

	//Добавление события для определенной даты
	void AddDateEvent(Date&_date, string event, string path);

	//Удаление одного события у выбранной даты
	void DeletEventDate(Date&_date, string& event, string path);

	//Удаление выбранной даты вместе со всеми событиями
	void DeleteDate(Date&_date, string path);

	//Поиск даты и вывод всех её событий (заранее отсортировыванных)
	void findDateEvents(const Date& _date);
	
	//Загрузка данных из файла в словарь
	void LoadDataFileInMap(const string& path);

	//Обновить порядок дат и событий файла в соответствии со словарем
	void UpdateTextFile(const string& path);
	
private:
	map<Date, vector<string>> DateEvents;
};
