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

	//Checks which date is further in the future.
	bool operator>(const Date& date) {

		//Checks which year is larger. If neither are, the two dates share the same date
		if (year > date.year) return 1;
		if (year < date.year) return 0;

		//Checks which month is larger, in case we are in the same year.
		//If neither are, we are in the same month.
		if (month > date.month) return 1;
		if (month < date.month) return 0;

		//Checks which date is larger, in case we are in the same year and month.
		//If both are equal, the > operator is false, hence only one comparison is needed.
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

		//Formula to conver Julian Calender Day to Julian Day Number
		// 367 * Y - (7 * (Y + 5001 + (M - 9)/7))/4 + (275 * M)/9 + D + 1729777
		//Where Y == Julian year, M == Julian month and D == Julian day
		//The formula is valid for Julian years >= -4712
		//Since we are well past said year, no hotels will be registering guests for the year -4711 or prior
		int julian_day_number1 = 367 * year - (7 * (year + 5001 + (month - 9) / 7)) / 4 + (275 * month) / 9 + day + 1729777;
		int julian_day_number2 = 367 * date.year - (7 * (date.year + 5001 + (date.month - 9) / 7)) / 4 + (275 * date.month) / 9 + date.day + 1729777;

		return julian_day_number1 - julian_day_number2;

	}
};




