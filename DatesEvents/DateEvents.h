#include "Date.h"

#include <iostream>
#include <vector>
#include <array>
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

	//���������� ������� ��� ������������ ����
	void AddDateEvent(Date& _date, string event, string path);

	//�������� ������ ������� � ��������� ����
	void DeletEventDate(Date& _date, string& event, string path);

	//�������� ��������� ���� ������ �� ����� ���������
	void DeleteDate(Date& _date, string path);

	//����� ���� � ����� ���� � ������� (������� �����������������)
	void findDateEvents(const Date& _date);

	//�������� ������ �� ����� � �������
	void LoadDataFileInMap(const string& path);

	//�������� ������� ��� � ������� ����� � ������������ �� ��������
	void UpdateTextFile(const string& path);

private:
	map<Date, vector<string>> DateEvents;
};

void ReadFileInConsole(const string& path);

