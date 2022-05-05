#pragma once
//#include <vector>
#include <string>
#include "Date.h"

class Room
{

	int room_number;
	int amount_of_beds;

	bool room_is_closed;
	std::string note;

	std::string guest_name;

	Date start_date;
	Date end_date;

public:

	//Initialised room
	Room();

	//Empty Room
	Room(const int room_number, const int amount_of_beds);

	//Room busy from Date A to Date B
	Room(const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, const std::string guest_name, const std::string note);

	//Closed room without a guest
	Room(const int room_number, const int amount_of_beds, const std::string note);

	//Room busy from Date A to Date B with a note
	Room(const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, const std::string note);

	Room operator= (const Room& room);

	bool operator> (const Room& room);
	bool operator< (const Room& room);

	//Function to close a room
	void close_room(std::string new_note);

	//Function to open a room
	void open_room();

	//Function to add a guest
	void add_guest(std::string guest, std::string new_note);

	//Getters
	/*
	
	int room_number;
	int amount_of_beds;

	bool room_is_closed;
	std::string note;

	std::string guest_name;

	Date start_date;
	Date end_date;
	*/

	int get_room_number();
	int get_amount_of_beds();
	bool get_is_room_closed();
	std::string get_note();
	std::string get_guest_name();
	Date get_start_date();
	Date get_end_date();

	//Setters
	void set_room_number(int new_number);
	void set_amount_of_beds(int new_amount_of_beds);
	void set_note(std::string new_note);
	void set_guest_name(std::string new_guest);
	void set_start_date(Date new_start_date);
	void set_end_date(Date new_end_date);

	void register_new_guest();

	int amount_of_days_room_is_taken();

};

