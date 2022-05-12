#pragma once
#include <stdexcept>
#include <fstream>
#include <ostream>
#include "Consts.h"

struct Date
{
	unsigned day; /**< Date's day. A number from 1 to 31 or less depending on the month. */
	unsigned month;  /**< Date's month. A number from 1 to 12. */
	unsigned year; /**< Date's year. Theoretically from -inf to +inf. In the program, must have a positive value. */


	/************************************************
	 *  Default Constructor.
	 ***********************************************/
	Date() : day(1), month(1), year(1) {}


	/************************************************
	 *  Constructor with given data.
	 ***********************************************/
	Date(unsigned day_, unsigned month_, unsigned year_) {

		bool valid_date = validate_date(day_, month_, year_);

		if (!valid_date) throw std::invalid_argument("Invalid date.");

		day = day_;
		month = month_;
		year = year_;

	}


	/************************************************
	 *  Function to check which date is later.
	 ***********************************************/
	bool operator>(const Date& date) {

		//Checks which year is larger. If neither are, the two dates share the same year.
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
	

	/************************************************
	 *  Function to check if two dates fall on the same date.
	 ***********************************************/
	bool operator== (const Date& date) {

		return year == date.year && month == date.month && day == date.day;

	}


	/************************************************
	 *  Function to check if a date is before another date.
	 ***********************************************/
	bool operator< (const Date& date) {

		return !(*this > date) && *this != date;

	}


	/************************************************
	 *  Function to check if a date is later to or on the same date as another date.
	 ***********************************************/
	bool operator>= (const Date& date) {

		return *this > date || *this == date;

	}


	/************************************************
	 *  Function to check if a date is before or on the same date as another date.
	 ***********************************************/
	bool operator<= (const Date& date) {

		return *this < date || *this == date;

	}


	/************************************************
	 *  Function to check if a date is on a different date than another date.
	 ***********************************************/
	bool operator!= (const Date& date) {

		return !(*this == date);

	}


	/************************************************
	 *  Function to check the amount of days between two dates.
	 ***********************************************/
	int operator- (const Date& date) const {

		//Formula to conver Julian Calender Day to Julian Day Number
		// 367 * Y - (7 * (Y + 5001 + (M - 9)/7))/4 + (275 * M)/9 + D + 1729777
		//Where Y == Julian year, M == Julian month and D == Julian day
		//The formula is valid for Julian years >= -4712
		//Since we are well past said year, no hotels will be registering guests for the year -4711 or prior
		int julian_day_number1 = 367 * year - (7 * (year + 5001 + (month - 9) / 7)) / 4 + (275 * month) / 9 + day + 1729777;
		int julian_day_number2 = 367 * date.year - (7 * (date.year + 5001 + (date.month - 9) / 7)) / 4 + (275 * date.month) / 9 + date.day + 1729777;

		return julian_day_number1 - julian_day_number2;

	}


	/************************************************
	 *  Function to read a date from a file.
	 ***********************************************/
	void read_from_file(std::ifstream& my_file) {

		//Reads the day, month and year
		my_file.read((char*)&day, sizeof(day));
		my_file.read((char*)&month, sizeof(month));
		my_file.read((char*)&year, sizeof(year));
		
		return;
	}

	/************************************************
	 *  Function to write a date to a file.
	 ***********************************************/
	void write_to_file(std::ofstream& my_file) {

		//Writes the day, month and years
		my_file.write((char*)&day, sizeof(day));
		my_file.write((char*)&month, sizeof(month));
		my_file.write((char*)&year, sizeof(year));		

		return;
	}

};




