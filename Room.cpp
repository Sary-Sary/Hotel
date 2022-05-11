#include "Room.h"

//Initialised room
Room :: Room() : room_number(0), amount_of_beds(0), room_is_closed(false) {}

//Empty Room
Room :: Room(const int room_number, const int amount_of_beds) : room_number(room_number), amount_of_beds(amount_of_beds), room_is_closed(false) {}

//Room busy from Date A to Date B
Room :: Room(const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, const std::string guest_name, const std::string note) :
	room_number(room_number), amount_of_beds(amount_of_beds), start_date(start_date), end_date(end_date), guest_name(guest_name), note(note), room_is_closed(true) {}

//Closed room without a guest
Room :: Room(const int room_number, const int amount_of_beds, const std::string note) :
	room_number(room_number), amount_of_beds(amount_of_beds), room_is_closed(true), note(note) {}

//Room busy from Date A to Date B with a note
Room :: Room(const int room_number, const int amount_of_beds, const Date start_date, const Date end_date, const std::string note) :
	room_number(room_number), amount_of_beds(amount_of_beds), start_date(start_date), end_date(end_date), note(note), room_is_closed(true) {}

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

bool Room::operator> (const Room& room) {

	return room_number > room.room_number;

}

bool Room::operator< (const Room& room) {

	return room_number < room.room_number;

}

bool Room::operator== (const int& room) {

	return room_number == room;

}

bool Room::operator> (const int& room) {

	return room_number > room;

}
bool Room::operator< (const int& room) {

	return room_number < room;

}

int Room::get_room_number() const { return room_number; }
int Room::get_amount_of_beds() const { return amount_of_beds; }
bool Room::get_is_room_closed() const { return room_is_closed; }
std::string Room::get_note() const { return note; }
std::string Room::get_guest_name() const { return guest_name; }
Date Room::get_start_date() const { return start_date; }
Date Room::get_end_date() const { return end_date; }

void Room::set_room_number(int new_number) {

	room_number = new_number;
	return;
}

void Room::set_amount_of_beds(int new_amount_of_beds) {

	amount_of_beds = new_amount_of_beds;
	return;
}

void Room::set_note(std::string new_note) {

	note = new_note;
	return;
}

void Room::set_guest_name(std::string new_guest) {

	guest_name = new_guest;
	return;
}

void Room::set_start_date(Date new_start_date) {

	start_date = new_start_date;
	return;
}

void Room::set_end_date(Date new_end_date) {

	end_date = new_end_date;
	return;
}

//Function to close a room
void Room::close_room(std::string new_note, Date start_date, Date end_date) {

	if (room_is_closed == true && guest_name != "") {

		std::cout << "\nRoom is taken. Please free the room before closing it.";
		return;
	}

	room_is_closed = true;
	set_note(new_note);
	set_start_date(start_date);
	set_end_date(end_date);

	return;

}

//Function to open a room
void Room::open_room() {

	room_is_closed = false;
	guest_name = "";
	note = "";

	set_start_date(Date());
	set_end_date(Date());

	return;

}

//Function to add a guest
void Room::add_guest(std::string guest, std::string new_note) {

	if (room_is_closed == true) {

		if (guest_name != "") std::cout << "\nRoom is already taken. Please chose another room.";
		else std::cout << "\nRoom is closed.";
	}

	set_guest_name(guest);
	set_note(new_note);
	room_is_closed = true;

	return;

}

void Room::register_new_guest(std::string guest_name, Date start_date, Date end_date, std::string note) {

	if (room_is_closed = true) {

		std::cout << "\nGuest could not be registered as the room is closed. Please chose a new room.";
		return;
	}

	add_guest(guest_name, note);
	set_start_date(start_date);
	set_end_date(end_date);
	return;
}

void Room::free_room() {

	if (room_is_closed == false) {

		std::cout << "\nRoom is already open";
		return;

	}

	open_room();
	return;
}

bool Room::room_is_closed_for_period(Date period_start, Date period_end) {

	if (room_is_closed == false) return false;
	return period_start > start_date && period_end < end_date;
}

int Room::amount_of_days_room_is_taken() { return end_date - start_date; }

void Room::read_from_file(std::ifstream& my_file) {

	if (!my_file) return;

	size_t size;
	char* data;

	my_file.read((char*)&room_number, sizeof(room_number));
	my_file.read((char*)&amount_of_beds, sizeof(amount_of_beds));

	my_file.read((char*)&room_is_closed, sizeof(room_is_closed));

	if (!my_file) return;

	my_file.read((char*)&size, sizeof(size));
	data = new char[size + 1];
	my_file.read(data, size);
	data[size] = '\0';
	set_note(data);
	delete data;

	my_file.read((char*)&size, sizeof(size));
	data = new char[size + 1];
	my_file.read(data, size);
	data[size] = '\0';
	set_guest_name(data);
	delete data;

	start_date.read_from_file(my_file);
	end_date.read_from_file(my_file);

	return;

}

void Room::write_to_file(std::ofstream& my_file) {

	my_file.write((char*)&room_number, sizeof(room_number));
	my_file.write((char*)&amount_of_beds, sizeof(amount_of_beds));

	my_file.write((char*)&room_is_closed, sizeof(room_is_closed));

	size_t size;

	size = note.size();
	my_file.write((char*)&size, sizeof(size));
	my_file.write((char*)note.c_str(), size);

	size = guest_name.size();
	my_file.write((char*)&size, sizeof(size));
	my_file.write((char*)guest_name.c_str(), size);

	start_date.write_to_file(my_file);
	end_date.write_to_file(my_file);

	return;

}
