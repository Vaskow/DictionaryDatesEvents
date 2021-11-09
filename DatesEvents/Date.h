struct Day {
	int value;
	explicit Day(int new_value) { //äîáàâèëè explicit, ÷òîáû íåÿâíî êîíñòðóêòîð íå âûçûâàëñÿ
		value = new_value;//ýòî ïîêàæåò, ãäå: äåíü, ìåñÿö èëè ãîä.
	}
};

struct Month {
	int value;
	explicit Month(int new_value) {
		value = new_value;
	}
};

struct Year {
	int value;
	explicit Year(int new_value) {
		value = new_value;
	}
};


struct Date
{
	int day;
	int month;
	int year;

	Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}
	Date(Day new_day, Month new_month, Year new_year)
	{
		day = new_day.value;
		month = new_month.value;
		year = new_year.value;
	}


	Date& operator=(const Date& _date)
	{
		if (this == &_date) {
			return *this;
		}
		day = _date.day;
		month = _date.month;
		year = _date.year;
		return *this;
	}
	bool operator==(const Date& _date)
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
	bool operator==(const Date& _date) const
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

	bool operator<(const Date& date1) const
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

};

