#pragma once
#include <iostream>

const unsigned month_to_date[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const unsigned MAX_MONTH = 12;
const std::string hotel_file_name = "hotel_room.dat";

//Checks if a year is a leapyear. 
//A leapyear is any year that is divisible by 4, but not divisible by 100, unless it is divisible by 400.
inline bool is_leapyear(const unsigned& year) {

	if (((year % 4 == 0) && (year % 100 != 0)) ||
		(year % 400 == 0)) return 1;

	return 0;
}

//Checks if a date is in February during a leapyear.
inline int is_feb_leapyear(const unsigned& month, const unsigned& year) {

	//If the year is a leapyear...
	if (is_leapyear(year)) {

		//...check if the month is february
		return month == 2 ? 1 : 0;

	}

	//If not, return 0
	return 0;

}

inline bool validate_date(const unsigned& day, const unsigned& month, const unsigned& year) {

	//Negative days and months are invalid.
	//Negative years aren't accepted, as online databases didn't exist before BC.
	if (day <= 0 || month <= 0 || year <= 0) return 0;

	if (month > MAX_MONTH) return 0;

	if ((day - is_feb_leapyear(month, year)) > month_to_date[month - 1]) return 0;

	return 1;

}
