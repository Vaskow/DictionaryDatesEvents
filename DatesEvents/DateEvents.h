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

	//���������� ������� ��� ������������ ����
	void AddDateEvent(Date& _date, string event);
	//�������� ������ ������� � ��������� ����
	void DeletEventDate(Date& _date, string& event);
	//�������� ��������� ���� ������ �� ����� ���������
	void DeleteDate(Date& _date);
	//����� ���� � ����� ���� � ������� (������� �����������������)
	void FindDateEvents(const Date& _date);
	//������ ����� ������� � ����� ������ �� �������
	void ReadFileInConsole();

private:

	//�������� ������� ��� � ������� ����� � ������������ �� ��������
	void UpdateTextFile();
	//�������� ������ �� ����� � �������
	void LoadDataFileInMap();
	//������ ��������� ����� ���� �� �������
	void PrintSliceDate(uint16_t slice_date, bool end);
	//������ ��������� ����� ���� � ����
	void WriteFileSliceDate(uint16_t slice_date, ofstream& ofs);

	map<Date, vector<string>> DateEvents;
	const string path;
};