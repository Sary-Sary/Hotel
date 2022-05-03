#pragma once
#include "Consts.h"

bool validate_date(unsigned day, unsigned month, unsigned year);

class Date
{
	unsigned day;
	unsigned month;
	unsigned year;

public:

	Date() : day(1), month(1), year(1) {}

	Date(unsigned day_, unsigned month_, unsigned year_) {

		validate_date(day_, month_, year_);

		day = day_;
		month = month_;
		year = year_;

	}



};

bool validate_date(unsigned day, unsigned month, unsigned year) {

	if (day == 0 || month == 0 || year == 0) return 0;

	if (month > 12) return 0;

	if (day + (year % 4 == 0) > month_to_date[month - 1]) return 0;

	return 1;

}