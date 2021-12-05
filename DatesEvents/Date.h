#include <cstdint>
#include <iostream>
#include <fstream>
using namespace std;

class Date
{
public:
	Date();
	Date(uint16_t new_day, uint16_t new_month, uint16_t new_year);

	Date& operator=(const Date& _date);
	bool operator==(const Date& _date);
	bool operator==(const Date& _date) const;
	bool operator<(const Date& date1) const;

	uint16_t GetYear() const;
	uint16_t GetMonth() const;
	uint16_t GetDay() const;

private:
	uint16_t day;
	uint16_t month;
	uint16_t year;
};

bool VerificDate(uint16_t day, uint16_t month, uint16_t year);
void PrintSliceDate(uint16_t slice_date, bool end);
void WriteFileSliceDate(uint16_t slice_date, ofstream& ofs);
