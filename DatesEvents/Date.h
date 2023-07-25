#include <cstdint>

class Date
{
public:
	Date();
	Date(uint16_t new_day, uint16_t new_month, uint16_t new_year);

	Date& operator=(const Date& _date);
	bool operator==(const Date& _date) const;
	bool operator<(const Date& date1) const;

	uint16_t GetYear() const;
	uint16_t GetMonth() const;
	uint16_t GetDay() const;

	//Проверка корректности даты
	static bool VerificDate(uint16_t day, uint16_t month, uint16_t year);

private:
	uint16_t day;
	uint16_t month;
	uint16_t year;
};