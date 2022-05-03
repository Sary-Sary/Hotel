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
	Room() : room_number(0), amount_of_beds(0), room_is_closed(false) {}

	//Empty Room
	Room (const int room_number, const int amount_of_beds) : room_number(room_number), amount_of_beds(amount_of_beds), room_is_closed(false) {}

	//Room busy from Date A to Date B
	Room (const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, std::string guest_name) : 
		  room_number(room_number), amount_of_beds(amount_of_beds), start_date (start_date), end_date(end_date), guest_name(guest_name) {}

	//Closed room without a guest
	Room(const int room_number, const int amount_of_beds, const std::string note) : 
		 room_number(room_number), amount_of_beds(amount_of_beds), room_is_closed(true), note (note) {}

	//Room busy from Date A to Date B with a note
	Room(const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, const std::string note) :
		room_number(room_number), amount_of_beds(amount_of_beds), start_date(start_date), end_date(end_date), note(note) {}

	Room operator= (const Room& room) {

		room_number = room.room_number;
		amount_of_beds = room.amount_of_beds;

		room_is_closed = room.room_is_closed;
		note = room.note;

		guest_name = room.guest_name;

		start_date = room.start_date;
		end_date = room.end_date;

		return;

	}

	//Function to close a room
	void close_room(std::string new_note) {

		room_is_closed = true;
		note = new_note;

		return;

	}

	//Function to open a room
	void open_room() {

		room_is_closed = false;
		note = "";

		return;

	}

	//Function to add a guest
	void add_guest(std::string guest, std::string new_note) {

		guest_name = guest;
		note = new_note;
		room_is_closed = true;

		return;

	}



};

