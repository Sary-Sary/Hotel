// Hotel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel_AVL.h"

Date create_date() {

	int day = 0;
	int month = 0;
	int year = 0;

	char char_dummy = 0;

	std::cout << "\nInsert the date in format [YYYY.MM.DD]: ";
	std::cin >> year >> char_dummy >> month >> char_dummy >> day;

	while (!validate_date(day, month, year)) {

		std::cout << "\nDate is invalid. Please reenter the date: ";
		std::cin >> year >> char_dummy >> month >> char_dummy >> day;

	}

	return Date(day, month, year);

}

//register guest
void register_guest(Hotel_AVL& hotel_rooms) {

	int room_number = 0; 
	std::string name; 
	std::string note;
	//Date start_date, Date end_date,
	
	std::cout << "\nPlease insert the name of the guest: ";
	std::cin >> name;

	std::cout << "\nInsert the room you would like to register " << name << ": ";
	std::cin >> room_number;

	std::cout << "[OPTIONAL]Add a note or press enter: ";
	std::cin >> note;

	std::cout << "\nAdding the starting date...";
	Date start_date = create_date();

	std::cout << "\nAdding the ending date...";
	Date end_date = create_date();

	while (start_date >= end_date) {

		std::cout << "\nThe end date must be after the starting date. Please change the end date.";
		end_date = create_date();

	}

	bool found_room = hotel_rooms.register_guest(room_number, name, start_date, end_date, note);

	while (!found_room) {

		std::cout << "\nRegistration failed - invalid room. Would you like to the change the room? [y/n]: ";

		char change_room = 'a';
		std::cin >> change_room;

		while (change_room != 'y' && change_room != 'n') {

			std::cout << "\nInvalid option. \nPlease insert either y or n: ";

		}

		if (change_room == 'n') break;

		std::cout << "\nPlease insert the new room number";
		std::cin >> room_number;

		found_room = hotel_rooms.register_guest(room_number, name, start_date, end_date, note);

	}

	std::cout << "\nRegistration process complete.";
	return;
}
 
void print_free_rooms(const std::list<Room>& rooms) {

	std::cout << "\nPrinting all free rooms for the given date...";

	for (auto it = rooms.begin(); it != rooms.end(); it++) {

		std::cout << "\n" << it->get_room_number();

	}

	return;
}

void all_free_rooms_during_date(Hotel_AVL& hotel_rooms) {

	std::cout << "\nInsert the date you would like to check for: ";
	Date date = create_date();

	std::list <Room> free_rooms;

	hotel_rooms.all_free_rooms_during_date(free_rooms, date);

	print_free_rooms(free_rooms);
	std::cout << "\nAll rooms have been printed.";

	return;
}

void free_room(Hotel_AVL& hotel_rooms) {

	int room_number = 0;
	std::cout << "\nInsert the room you would like to free: ";
	std::cin >> room_number;

	bool room_found = hotel_rooms.free_a_room(room_number);

	while (!room_found) {

		std::cout << "\nInvalid room. Would you like to insert a new room to free? [y/n]: ";

		char change_room = 'a';
		std::cin >> change_room;

		while (change_room != 'y' && change_room != 'n') {

			std::cout << "\nInvalid option. \nPlease insert either y or n: ";

		}

		if (change_room == 'n') break;

		std::cout << "\nPlease insert the new room number: ";
		std::cin >> room_number;

		room_found = hotel_rooms.free_a_room(room_number);
	}

	std::cout << "\nProcess complete.";

	return;

}

std::string close_room_file_name(Date start_date) {
	
	std::string name = "report";
	name += "-";
	name += std::to_string(start_date.year);
	name += "-";
	name += std::to_string(start_date.month);
	name += "-";
	name += std::to_string(start_date.day);
	name += ".txt";	
		 
	return name;
}

void create_closed_rooms_file(Date start_date, std::list <Room> rooms) {

	std::ofstream my_file;

	std::string file_name = close_room_file_name(start_date);
	my_file.open(file_name, std::ios::out);

	if (!my_file) {

		std::cerr << "Could not open file.";
		return;

	}

	for (auto it = rooms.begin(); it != rooms.end(); it++) {

		my_file << "Room: ";
		my_file << std::to_string(it->get_room_number());
		my_file << "\nAmount of days: ";
		my_file << std::to_string(it->amount_of_days_room_is_taken());
		my_file << "\n___________\n";
	}

	my_file.close();

}

void closed_room_inquiry(Hotel_AVL& hotel_rooms) {

	std::cout << "\nInserting the start date for the inquiry...";
	Date start_date = create_date();

	std::cout << "\nInserting the end date for the inquiry...";
	Date end_date = create_date();

	std::list <Room> rooms;
	hotel_rooms.closed_room_inquiry(rooms, start_date, end_date);

	create_closed_rooms_file(start_date, rooms);
	
	std::cout << "\nProcess complete.";

	return;
}

void find_room(Hotel_AVL& hotel_rooms) {
	
	int min_amount_of_beds = 0;
	std::cout << "\nInsert the minimum amount of beds needed: ";
	std::cin >> min_amount_of_beds;

	Room room;
	bool at_least_one_room_was_found = false;
	hotel_rooms.find_room_min_beds(min_amount_of_beds, room, at_least_one_room_was_found);

	if (!at_least_one_room_was_found) {

		std::cout << "\nFailed to find a room with " << min_amount_of_beds << "beds.";
		return;
	}

	std::cout << "\nRoom " << room.get_room_number() << " is the best possible room.";
	std::cout << "\nProcess complete.";
	return;
}

void close_room(Hotel_AVL& hotel_rooms) {

	int room_number = 0;
	std::string note;

	std::cout << "\nInsert the room you would like to close: ";
	std::cin >> room_number;

	std::cout << "Add a note explaining why the room is closed: ";
	std::cin >> note;

	std::cout << "\nAdding the starting date...";
	Date start_date = create_date();

	std::cout << "\nAdding the ending date...";
	Date end_date = create_date();

	while (start_date >= end_date) {

		std::cout << "\nThe end date must be after the starting date. Please change the end date.";
		end_date = create_date();

	}

	bool found_room = hotel_rooms.close_room(room_number, note, start_date, end_date);

	while (!found_room) {

		std::cout << "\nCould not close room - invalid room. Would you like to the change the room? [y/n]: ";

		char change_room = 'a';
		std::cin >> change_room;

		while (change_room != 'y' && change_room != 'n') {

			std::cout << "\nInvalid option. \nPlease insert either y or n: ";

		}

		if (change_room == 'n') break;

		std::cout << "\nPlease insert the new room number";
		std::cin >> room_number;

		found_room = hotel_rooms.close_room(room_number, note, start_date, end_date);

	}

	std::cout << "\nProcess complete.";

}

void read_hotel_rooms(Hotel_AVL& hotel) {

	std::ifstream my_file;

	my_file.open(hotel_file_name, std::ios::binary);

	if (!my_file) {

		std::cerr << "Could not open file.";
		return;

	}

	Room temp;

	while (!my_file.eof()) {

		temp.read_from_file(my_file);

		if (my_file) hotel.insert(temp);

	}

	my_file.close();

}

void create_hotel_file() {

	Room r1 (100, 3, Date(4, 8, 2022), Date(16, 8, 2022), "Grian", "Pesky bird...");
	Room r2 (101, 2);
	Room r3 (102, 2, Date(5, 8, 2022), Date(2, 10, 2022), "Closed for renovations.");
	Room r4 (200, 3, Date(1, 8, 2022), Date(24, 8, 2022), "Scar", "Hawkeye!");
	Room r5 (201, 2, Date(8, 8, 2022), Date(5, 9, 2022), "Pearl", "Want some soup, I got some soup~");
	Room r6 (202, 2, Date(23, 8, 2022), Date(12, 9, 2022), "Scott", "Dang, that's a long name");
	Room r7 (300, 3, Date(3, 8, 2022), Date(29, 9, 2022), "Definitely no withers here.");
	Room r8 (301, 2);
	Room r9 (302, 2);
	Room r10 (400, 5, Date(8, 8, 2022), Date(9, 9, 2022), "Hermits", "Hermitgang, Hermitgang, Hermitgang");

	std::ofstream my_file;
	my_file.open(hotel_file_name, std::ios::binary);

	if (!my_file) {

		std::cerr << "";
		return;
	}

	r1.write_to_file(my_file);
	r2.write_to_file(my_file);
	r3.write_to_file(my_file);
	r4.write_to_file(my_file);
	r5.write_to_file(my_file);
	r6.write_to_file(my_file);
	r7.write_to_file(my_file);
	r8.write_to_file(my_file);
	r9.write_to_file(my_file);
	r10.write_to_file(my_file);

	my_file.close();

	return;

}

int main()
{

	create_hotel_file();
	Hotel_AVL hotel_rooms;
	read_hotel_rooms(hotel_rooms);

	std::list <Room> rooms_list;
	hotel_rooms.all_free_rooms_during_date(rooms_list, Date(10, 8, 2022));
	print_free_rooms(rooms_list);

	rooms_list.clear();

	hotel_rooms.free_a_room(102);

	hotel_rooms.closed_room_inquiry(rooms_list, Date(10, 8, 2022), Date(10, 9, 2022));
	create_closed_rooms_file(Date(10, 8, 2022), rooms_list);

	Room room;
	bool bed_found = false;

	hotel_rooms.find_room_min_beds(1, room, bed_found);

	if (!bed_found) std::cout << "\nNo bed found";
	else std::cout << "\nRoom with min beds: " << room.get_room_number();
	
}
