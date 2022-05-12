#pragma once
//#include <vector>
#include <string>
#include "Date.h"

class Room
{

	int room_number; /**< Room's number. A sparkly tag in front of the room so guests know where they are staying. */
	int amount_of_beds; /**< How many beds a room has. Useful for deciding where guests should sleep.*/

	bool room_is_closed; /**< A bool for whether a room is currently closed or not. Open rooms can accept new guests. */
	std::string note; /**< A note to a room. Either explains why a room is closed, or indicates something a guest may desire. */

	std::string guest_name; /**< The name of the guest in the room. Important to not misname guest's, it is rude. */

	Date start_date; /**< The starting date when a room is taken. */
	Date end_date; /**< The  ate when a room is freed. */

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

	bool operator> (const Room& room) const;
	bool operator< (const Room& room) const;

	bool operator== (const int& room);
	bool operator> (const int& room);
	bool operator< (const int& room);

	//Function to close a room
	void close_room(std::string new_note, Date start_date, Date end_date);

	//Function to open a room
	void open_room();

	//Function to add a guest
	void add_guest(std::string guest, std::string new_note);

	//Getters

	int get_room_number() const;
	int get_amount_of_beds() const;
	bool get_is_room_closed() const;
	std::string get_note() const;
	std::string get_guest_name() const;
	Date get_start_date() const;
	Date get_end_date() const;

	//Setters
	void set_room_number(int new_number);
	void set_amount_of_beds(int new_amount_of_beds);
	void set_note(std::string new_note);
	void set_guest_name(std::string new_guest);
	void set_start_date(Date new_start_date);
	void set_end_date(Date new_end_date);

	void register_new_guest(std::string guest_name, Date start_date, Date end_date, std::string note);
	void free_room();

	int amount_of_days_room_is_taken() const;
	bool room_is_closed_for_period(Date period_start, Date period_end);

	void read_from_file(std::ifstream& my_file);
	void write_to_file(std::ofstream& my_file);
};

