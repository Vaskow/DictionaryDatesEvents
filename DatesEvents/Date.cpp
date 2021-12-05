#include "Date.h"

Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(uint16_t new_day, uint16_t new_month, uint16_t new_year)
{
	day = new_day;
	month = new_month;
	year = new_year;
}

Date& Date::operator=(const Date& _date)
{
	if (this == &_date) {
		return *this;
	}
	day = _date.day;
	month = _date.month;
	year = _date.year;
	return *this;
}
bool Date::operator==(const Date& _date)
{
	if (this == &_date) {
		return true;
	}
	else if (day == _date.day && month == _date.month && year == _date.year)
	{
		return true;
	}
	else return false;

}
bool Date::operator==(const Date& _date) const
{
	if (this == &_date) {
		return true;
	}
	else if (day == _date.day && month == _date.month && year == _date.year)
	{
		return true;
	}
	else return false;

}

bool Date::operator<(const Date& date1) const
{
	if (year == date1.year)
	{
		if (month == date1.month)
		{
			return day < date1.day;
		}
		else return month < date1.month;
	}
	else return year < date1.year;
}

uint16_t Date::GetDay() const {
	return day;
}

uint16_t Date::GetMonth() const {
	return month;
}

uint16_t Date::GetYear() const {
	return year;
}

bool VerificDate(uint16_t day, uint16_t month, uint16_t year)
{
	if (year > 2022)
	{
		return false;
	}
	else if (month > 0 && month <= 7)
	{
		if ((month % 2) == 0)
		{
			if (month == 2 && (year % 4 == 0 || year % 400 == 0))
			{
				if (day > 0 && day <= 29)
				{
					return true;
				}
			}
			else if (month == 2 && (year % 4 != 0 && year % 400 != 0))
			{
				if (day > 0 && day <= 28)
				{
					return true;
				}
			}
			else if (day > 0 && day <= 30)
			{
				return true;
			}
		}
		else
		{
			if (day > 0 && day <= 31)
			{
				return true;
			}
		}
	}
	else if (month > 0 && month >= 8 && month <= 12)
	{
		if ((month % 2) == 0)
		{
			if (day > 0 && day <= 31)
			{
				return true;
			}
		}
		else
		{
			if (day > 0 && day <= 30)
			{
				return true;
			}
		}
	}

	return false;

}

void PrintSliceDate(uint16_t slice_date, bool end)
{
	char point = '.';
	if (end) { point = ' '; }

	if (slice_date < 10) { cout << "0" << slice_date << point; }
	else { cout << slice_date << point; }
}

void WriteFileSliceDate(uint16_t slice_date, ofstream &ofs)
{
	if (slice_date < 10) { ofs << "0" << slice_date << " "; }
	else { ofs << slice_date << " "; }
}
