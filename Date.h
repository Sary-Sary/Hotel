#pragma once
#include <stdexcept>
#include "Consts.h"

struct Date
{
	unsigned day;
	unsigned month;
	unsigned year;

	Date() : day(1), month(1), year(1) {}

	Date(unsigned day_, unsigned month_, unsigned year_) {

		bool valid_date = validate_date(day_, month_, year_);

		if (!valid_date) throw std::invalid_argument("Invalid date.");

		day = day_;
		month = month_;
		year = year_;

	}

	//3 March 2009 to 1 Feb 2009

	bool operator>(const Date& date) {

		if (year > date.year) return 1;
		if (year < date.year) return 0;

		if (month > date.month) return 1;
		if (month < date.month) return 0;

		if (day > date.day) return 1;
		return 0;

	}
	
	bool operator== (const Date& date) {

		return year == date.year && month == date.month && day == date.day;

	}

	bool operator< (const Date& date) {

		return !(*this > date);

	}

	bool operator>= (const Date& date) {

		return *this > date || *this == date;

	}

	bool operator<= (const Date& date) {

		return *this < date || *this == date;

	}

	bool operator!= (const Date& date) {

		return !(*this == date);

	}

	bool operator- (const Date& date) {

		int julian_day_number1 = 367 * year - (7 * (year + 5001 + (month - 9) / 7)) / 4 + (275 * month) / 9 + day + 1729777;
		int julian_day_number2 = 367 * date.year - (7 * (date.year + 5001 + (date.month - 9) / 7)) / 4 + (275 * date.month) / 9 + date.day + 1729777;

		return julian_day_number1 - julian_day_number2;

	}
};




