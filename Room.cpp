#include "Room.h"

/************************************************
 *  Initialise room, default constructor.
 ***********************************************/
Room :: Room() : room_number(0), amount_of_beds(0), room_is_closed(false) {}

/************************************************
 *  Constructor of an empty room that is open.
 ***********************************************/
Room :: Room(const int room_number, const int amount_of_beds) : room_number(room_number), amount_of_beds(amount_of_beds), room_is_closed(false) {}

/************************************************
 * Constructor of a room that has a guest in it from Date A until Date B.
 ***********************************************/
Room :: Room(const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, const std::string guest_name, const std::string note) :
	room_number(room_number), amount_of_beds(amount_of_beds), start_date(start_date), end_date(end_date), guest_name(guest_name), note(note), room_is_closed(true) {}

/************************************************
 * Constructor of a room that is closed with a note.
 ***********************************************/
Room :: Room(const int room_number, const int amount_of_beds, const std::string note) :
	room_number(room_number), amount_of_beds(amount_of_beds), room_is_closed(true), note(note) {}

/************************************************
 *  Constructor of a room that is closed with a note from Date A to Date B.
 ***********************************************/
Room :: Room(const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, const std::string note) :
	room_number(room_number), amount_of_beds(amount_of_beds), start_date(start_date), end_date(end_date), note(note), room_is_closed(true) {}

/************************************************
 *  Overloads = operator for Room class.
 ***********************************************/
Room Room::operator= (const Room& room) {

	room_number = room.room_number;
	amount_of_beds = room.amount_of_beds;

	room_is_closed = room.room_is_closed;
	note = room.note;

	guest_name = room.guest_name;

	start_date = room.start_date;
	end_date = room.end_date;

	return *this;

}

/************************************************
 *  Overloads > operator. Returns which room has a larger room number.
 ***********************************************/
bool Room::operator> (const Room& room) const {

	return room_number > room.room_number;

}

/************************************************
 *  Overloads < operator. Returns which room has a smaller room number.
 ***********************************************/
bool Room::operator< (const Room& room) const {

	return room_number < room.room_number;

}

/************************************************
 *  Overloads == operator. Returns whether the room's number corresponds to the seeked number.
 ***********************************************/
bool Room::operator== (const int& room) {

	return room_number == room;

}

/************************************************
 *  Overloads > operator with int. Returns whether the room has a larger room number than [int].
 ***********************************************/
bool Room::operator> (const int& room) {

	return room_number > room;

}

/************************************************
 *  Overloads < operator with int. Returns whether the room has a smaller room number than [int].
 ***********************************************/
bool Room::operator< (const int& room) {

	return room_number < room;

}


/************************************************
 *	Getters
 ***********************************************/
 //! <Gets room number> 
int Room::get_room_number() const { return room_number; }  
//! <Gets the amount of beds a room has>
int Room::get_amount_of_beds() const { return amount_of_beds; } 
//! <Gets if the room is closed>
bool Room::get_is_room_closed() const { return room_is_closed; } 
//! <Gets room's note>
std::string Room::get_note() const { return note; }  
//! <Gets room's guest>
std::string Room::get_guest_name() const { return guest_name; }  
//! <Gets room's start date>
Date Room::get_start_date() const { return start_date; }
//! <Gets room's end date>
Date Room::get_end_date() const { return end_date; }   

//! <Sets room number> 
void Room::set_room_number(int new_number) {

	room_number = new_number;
	return;
}

//! <Sets the amount of beds a room has>
void Room::set_amount_of_beds(int new_amount_of_beds) {

	amount_of_beds = new_amount_of_beds;
	return;
}

//! <Sets if the room is closed>
void Room::set_note(std::string new_note) {

	note = new_note;
	return;
}

//! <Sets room's note>
void Room::set_guest_name(std::string new_guest) {

	guest_name = new_guest;
	return;
}

//! <Sets room's start date>
void Room::set_start_date(Date new_start_date) {

	start_date = new_start_date;
	return;
}

//! <Sets room's end dateS>
void Room::set_end_date(Date new_end_date) {

	end_date = new_end_date;
	return;
}

/************************************************
 *  Function to close a room.
 *	Function recieves a now, start date and end date. If valid, room is changed and closed.
 ***********************************************/
void Room::close_room(std::string new_note, Date start_date, Date end_date) {

	//If the room has a guest inside it...
	if (room_is_closed == true && guest_name != "") {

		//... returns that it cannot close the room.
		std::cout << "\nRoom is taken. Please free the room before closing it.";
		return;
	}

	//Sets room to closed and changes the necessary data
	room_is_closed = true;
	set_note(new_note);
	set_start_date(start_date);
	set_end_date(end_date);

	std::cout << "\nRoom succesfully closed!";

	return;

}

/************************************************
 *  Function to set a room as open.
 ***********************************************/
void Room::open_room() {

	room_is_closed = false;
	guest_name = "";
	note = "";

	set_start_date(Date());
	set_end_date(Date());

	return;

}

/************************************************
 *  Function to add a guest.
 *	Function recieves the guest's name and a note. Changes room data.
 ***********************************************/
void Room::add_guest(std::string guest, std::string new_note) {

	//Adds guest data to room
	set_guest_name(guest);
	set_note(new_note);
	room_is_closed = true;

	return;

}


/************************************************
 *  Function to register a new guest.
 *	Adds guest to room and adds the period the guest is taking the room. Validates if room can be taken or not.
 ***********************************************/
void Room::register_new_guest(std::string guest_name, Date start_date, Date end_date, std::string note) {

	//If room is closed...
	if (room_is_closed == true) {

		//... checks if it has a guest or not and shows the according message.
		if (guest_name != "") std::cout << "\nRoom is already taken. Please chose another room.";
		else std::cout << "\nRoom is closed. Please chose another room.";

		return;
	}

	//Adds guest and dates
	add_guest(guest_name, note);
	set_start_date(start_date);
	set_end_date(end_date);

	std::cout << "\nGuest succesfully registered!";

	return;
}

/************************************************
 *  Function to free a room.
 *	Validates if room can be freed before opening it.
 ***********************************************/
void Room::free_room() {

	//If room is open...
	if (room_is_closed == false) {

		//... returns immediately.
		std::cout << "\nRoom is already open!";
		return;

	}

	//Else, opens room
	open_room();

	std::cout << "\nRoom succesfully opened!";

	return;
}

/************************************************
 *  Function to check if room is closed for a given period.
 *	Function recieves two dates and checks if the room is taken for the two dates.
 ***********************************************/
bool Room::room_is_closed_for_period(Date period_start, Date period_end) {

	//If room is closed, it is not taken for the given period
	if (room_is_closed == false) return false;
	//If it is open, check if the dates the room is taken for fall into the given period.
	return period_start > start_date && period_end < end_date;
}

/************************************************
 *  Function to return the amount of time a room is taken for.
 ***********************************************/
int Room::amount_of_days_room_is_taken() const { return end_date - start_date; } 

/************************************************
 *  Function to read a room from a file.
 ***********************************************/
void Room::read_from_file(std::ifstream& my_file) {

	//If file isn't open, return.
	if (!my_file) return;

	size_t size;
	char* data;

	//Reads the room number and amount of beds.
	my_file.read((char*)&room_number, sizeof(room_number));
	my_file.read((char*)&amount_of_beds, sizeof(amount_of_beds));
	
	//Reads if the room is closed or not
	my_file.read((char*)&room_is_closed, sizeof(room_is_closed));

	if (!my_file) return;

	//Reads how long the string for the note is and then reads the note
	my_file.read((char*)&size, sizeof(size));
	data = new char[size + 1];
	my_file.read(data, size);
	data[size] = '\0';
	set_note(data);
	delete data;

	//Reads how long the string for the guest's name is and then reads the name
	my_file.read((char*)&size, sizeof(size));
	data = new char[size + 1];
	my_file.read(data, size);
	data[size] = '\0';
	set_guest_name(data);
	delete data;

	//Calls two functions to read the start and end date
	start_date.read_from_file(my_file);
	end_date.read_from_file(my_file);

	return;

}

/************************************************
 *  Function to write a room to a file.
 ***********************************************/
void Room::write_to_file(std::ofstream& my_file) {

	//Writes the room number and amount of beds.
	my_file.write((char*)&room_number, sizeof(room_number));
	my_file.write((char*)&amount_of_beds, sizeof(amount_of_beds));

	//Writes if the room is closed or not
	my_file.write((char*)&room_is_closed, sizeof(room_is_closed));

	size_t size;

	//Writes how long the string for the note is and then writes the note
	size = note.size();
	my_file.write((char*)&size, sizeof(size));
	my_file.write((char*)note.c_str(), size);


	//Writes how long the string for the guest's name is and then writes the name
	size = guest_name.size();
	my_file.write((char*)&size, sizeof(size));
	my_file.write((char*)guest_name.c_str(), size);

	//Calls two functions to write the start and end date
	start_date.write_to_file(my_file);
	end_date.write_to_file(my_file);

	return;

}
