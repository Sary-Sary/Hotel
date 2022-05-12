/*

Faculty Number: 82101
GitHub: https://github.com/Sary-Sary/Hotel

*/

#include <iostream>
#include "Hotel_AVL.h"

/************************************************
 *  Function to create and return a valid date via user input.
 *	Function prompts the user to enter the needed data to create a date and validates if the data is correct or not.
 ***********************************************/
Date create_date() {

	int day = 0;
	int month = 0;
	int year = 0;

	char char_dummy = 0;

	//Prompts user to enter date.
	std::cout << "\nInsert the date in format [YYYY.MM.DD]: ";
	std::cin >> year >> char_dummy >> month >> char_dummy >> day;

	//If the date is not valid...
	while (!validate_date(day, month, year)) {

		//Prompts user to enter date.
		std::cout << "\nDate is invalid. Please reenter the date: ";
		std::cin >> year >> char_dummy >> month >> char_dummy >> day;

	}

	return Date(day, month, year);

}

/************************************************
 *  Function to initiate the registration of a guest through user input. 
 *	Function requires valid input of all necessary data to register a new guest, validates the data if needed,
 *	then calls a function to continue to registration process.
 ***********************************************/
void register_guest(Hotel_AVL& hotel_rooms) {

	//The data needed to register a guest
	int room_number = 0; 
	std::string name; 
	std::string note;
	
	//Block for user input of the guest's name
	std::cout << "\nPlease insert the name of the guest: ";
	std::cin >> name;
	std::cin.ignore();

	//Block for user input of the room the guest will stay in
	std::cout << "\nInsert the room you would like to register " << name << ": ";
	std::cin >> room_number;
	std::cin.ignore();

	//Block to see if the guest has an additional note for their room.
	std::cout << "\nWould you like to add a note for the room? Please insert 1 if you would like to add a note and 0 if not.";
	int choice = 0;

	std::cin >> choice;
	std::cin.ignore();

	while (choice != 0 && choice != 1) {

		std::cout << "\nInvalid entry. Please insert 1 if you would like to add a note and 0 if not.";
		std::cin >> choice;
		std::cin.ignore();

	}

	//If the user would like to add a guest's note...
	if (choice == 1) {

		//... input starts here
		std::cout << "[OPTIONAL]Add a note or press enter: \n";
		std::cin >> note;
		std::cin.ignore();

	}

	//Block to add the starting date.
	std::cout << "\nAdding the starting date...";
	Date start_date = create_date();

	//Block to add the ending date.
	std::cout << "\nAdding the ending date...";
	Date end_date = create_date();

	//Checks if the starting date is before the ending date
	while (start_date >= end_date) {

		//If not, requests a new end dat until a valid one is given.
		std::cout << "\nThe end date must be after the starting date. Please change the end date.";
		end_date = create_date();

	}

	//Function that takes in the data and begins registration
	//Returns if the room exists in the hotel or not. 
	bool found_room = hotel_rooms.register_guest(room_number, name, start_date, end_date, note);

	//If the room doesn't exist...
	while (!found_room) {

		//Informs the user and asks if they would like to change the room or finish registration.
		std::cout << "\nRegistration failed - invalid room. Would you like to the change the room? [y/n]: ";

		//User inputs their choice
		char change_room = 'a';
		std::cin >> change_room;

		//If user input is invalid...
		while (change_room != 'y' && change_room != 'n') {

			//Program prompts them to re-enter
			std::cout << "\nInvalid option. \nPlease insert either y or n: ";
			std::cin >> change_room;

		}

		//If user does not wish to enter a new room, ends the process without registering a new guest
		if (change_room == 'n') break;

		//Else, prompts user to enter a new room number...
		std::cout << "\nPlease insert the new room number";
		std::cin >> room_number;

		//... and attempts to register guest and see if the newly entered room exists
		found_room = hotel_rooms.register_guest(room_number, name, start_date, end_date, note);

	}

	std::cout << "\nRegistration process complete.";
	return;
}


/************************************************
 *  Function to print all free rooms.
 *	Function recieves an ordereed set of rooms and prints out the room number of the rooms in said set. 
 ***********************************************/
void print_free_rooms(const std::set<Room>& rooms) {

	std::cout << "\nPrinting all free rooms for the given date...";

	for (auto it = rooms.begin(); it != rooms.end(); it++) {

		std::cout << "\n" << it->get_room_number();

	}

	return;
}

/************************************************
 *  Function to find all free rooms during a user indicated period of time.
 *	Function recieves a tree containing all hotel rooms, requests the user to give a date of inquiry,
 *	and prints out which rooms are free for the inserted date.
 ***********************************************/
void all_free_rooms_during_date(Hotel_AVL& hotel_rooms) {

	//Prompts user to insert date.
	std::cout << "\nInsert the date you would like to check for: ";
	Date date = create_date();

	std::set <Room> free_rooms;

	//Parses through the hotel rooms to find a free room during the given period.
	hotel_rooms.all_free_rooms_during_date(free_rooms, date);

	//Function to print free rooms.
	print_free_rooms(free_rooms);
	std::cout << "\nAll rooms have been printed.";

	return;
}

/************************************************
 *  Function to free a given room.
 *	Function recieves a tree with all hotel rooms and requests the user to choose a room to free.
 ***********************************************/
void free_room(Hotel_AVL& hotel_rooms) {

	//Prompts user to insert room to be opened.
	int room_number = 0;
	std::cout << "\nInsert the room you would like to free: ";
	std::cin >> room_number;

	//Function to attempt to free room, if the inserted room can be found.
	bool room_found = hotel_rooms.free_a_room(room_number);

	//If the room foes not exists...
	while (!room_found) {

		//Informs the user and asks if they would like to change the room or continue without opening a room.
		std::cout << "\nInvalid room. Would you like to insert a new room to free? [y/n]: ";

		//User inputs their choice
		char change_room = 'a';
		std::cin >> change_room;

		//If user input is invalid...
		while (change_room != 'y' && change_room != 'n') {

			//Program prompts them to re-enter
			std::cout << "\nInvalid option. \nPlease insert either y or n: ";

		}

		//If user does not wish to enter a new room, ends the process without opening any rooms
		if (change_room == 'n') break;

		//Else, prompts user to enter a new room number...
		std::cout << "\nPlease insert the new room number: ";
		std::cin >> room_number;

		//... and attempts to free the new room and check if said room exists
		room_found = hotel_rooms.free_a_room(room_number);
	}

	std::cout << "\nProcess complete.";

	return;

}

/************************************************
 *  Function to create a closed room inquiry file based on a given Date.
 *	For Date YYYY.MM.DD, the file has the format report-YYYY-MM-DD.txt
 ***********************************************/
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

/************************************************
 *  Function to create a txt from a set of rooms.
 *	Function recieves a date and a set of rooms, opening a file based on the date. After opening the file,
 *	the function adds each room to the file, adding the room number and the amount of days the room is taken for.
 ***********************************************/
void create_closed_rooms_file(Date start_date, std::set <Room> rooms) {

	//Creates file
	std::ofstream my_file;

	//Generates the file name and opens the file
	std::string file_name = close_room_file_name(start_date);
	my_file.open(file_name, std::ios::out);

	//Checks if the file opened succesfully...
	if (!my_file) {

		//... if not, creates an error message.
		std::cerr << "Could not open file.";
		return;

	}

	//Adds every room to the file in a given format
	/*
	   Room: [room_number]
	   Amount of days: [amount of days the room is taken]
	   ___________
	*/
	for (auto it = rooms.begin(); it != rooms.end(); it++) {

		my_file << "Room: ";
		my_file << std::to_string(it->get_room_number());
		my_file << "\nAmount of days: ";
		my_file << std::to_string(it->amount_of_days_room_is_taken());
		my_file << "\n___________\n";
	}

	//Closes file
	my_file.close();

	std::cout << "\nInquiry succesfully saved to " << file_name << ".";

}

/************************************************
 *  Function to initiate creating a closed room inquiry.
 *	Function recieves a tree with the hotel rooms and, based on the two dates inputted by the user,
 *	finds which rooms are taken during the two dates before adding all dates to a file.
 ***********************************************/
void closed_room_inquiry(Hotel_AVL& hotel_rooms) {

	//User input for the start date
	std::cout << "\nInserting the start date for the inquiry...";
	Date start_date = create_date();

	//User input for the end date
	std::cout << "\nInserting the end date for the inquiry...";
	Date end_date = create_date();

	//Checks if the starting date is before the ending date
	while (start_date >= end_date) {

		//If not, requests a new end dat until a valid one is given.
		std::cout << "\nThe end date must be after the starting date. Please change the end date.";
		end_date = create_date();

	}

	//Finds which rooms is taken between the two dates
	std::set <Room> rooms;
	hotel_rooms.closed_room_inquiry(rooms, start_date, end_date);

	//Creates the file with the rooms
	create_closed_rooms_file(start_date, rooms);
	
	std::cout << "\nProcess complete.";

	return;
}


/************************************************
 *  Function to find a room that has a minimum of x beds.
 *	Function recieves a tree of hotel rooms and, based on a user input, finds which room has at least x amount of beds.
 *	The function prioritises rooms with less beds.
 ***********************************************/
void find_room(Hotel_AVL& hotel_rooms) {
	
	//Prompts user to include how many beds are needed
	int min_amount_of_beds = 0;
	std::cout << "\nInsert the minimum amount of beds needed: ";
	std::cin >> min_amount_of_beds;

	//Calls unction to find a room with x amount of beds that returns if the bed was found
	Room room;
	bool at_least_one_room_was_found = false;
	hotel_rooms.find_room_min_beds(min_amount_of_beds, room, at_least_one_room_was_found);

	//If no bed was found...
	if (!at_least_one_room_was_found) {

		//... tells the user that no bed could be found
		std::cout << "\nFailed to find a room with " << min_amount_of_beds << " beds.";
		return;
	}

	//Else, tells the user the best potential bed
	std::cout << "\nRoom " << room.get_room_number() << " is the best possible room.";
	std::cout << "\nProcess complete.";
	return;
}


/************************************************
 *  Function to initiate closing a room.
 *	Function recieves a tree of rooms and requests the user to insert the room they would like to close,
 *	along with a note explaining why said room was closed and the period of time it will be closed for.
 *	Checks if room can be closed.
 ***********************************************/
void close_room(Hotel_AVL& hotel_rooms) {

	int room_number = 0;
	std::string note;

	//Prompts user to insert room number
	std::cout << "\nInsert the room you would like to close: ";
	std::cin >> room_number;

	std::cin.ignore();

	//Prompts user to add a note explaining why the room was closed
	std::cout << "Add a note explaining why the room is closed: ";
	std::cin >> note;

	std::cin.ignore();

	//Prompts user to add a start and end date
	std::cout << "\nAdding the starting date...";
	Date start_date = create_date();

	std::cout << "\nAdding the ending date...";
	Date end_date = create_date();

	//If the end date is before the start date...
	while (start_date >= end_date) {

		//... prompts the user to change the end date.
		std::cout << "\nThe end date must be after the starting date. Please change the end date.";
		end_date = create_date();

	}

	//Attempts to close room, returns if room could be found
	bool found_room = hotel_rooms.close_room(room_number, note, start_date, end_date);

	//If room could not be found...
	while (!found_room) {

		//Informs the user and asks if they would like to change the room or continue without closing a room.
		std::cout << "\nCould not close room - invalid room. Would you like to the change the room? [y/n]: ";

		//User inputs their choice
		char change_room = 'a';
		std::cin >> change_room;

		//If user input is invalid...
		while (change_room != 'y' && change_room != 'n') {

			//Program prompts them to re-enter
			std::cout << "\nInvalid option. \nPlease insert either y or n: ";

		}

		//If user does not wish to enter a new room, ends the process without opening any rooms
		if (change_room == 'n') break;

		//Else, prompts user to enter a new room number...
		std::cout << "\nPlease insert the new room number: ";
		std::cin >> room_number;

		//... and attempts to close the new room and check if said room exists
		found_room = hotel_rooms.close_room(room_number, note, start_date, end_date);

	}

	std::cout << "\nProcess complete.";

}

/************************************************
 *  Function to read a binary file and create all hotel rooms.
 *	Function recieves a tree of rooms and reads the file into the tree, inserting every room one by one.
 ***********************************************/
void read_hotel_rooms(Hotel_AVL& hotel) {

	//Creates file
	std::ifstream my_file;

	//Opens file
	my_file.open(hotel_file_name, std::ios::binary);

	//If file failed to open...
	if (!my_file) {

		//... input error message and exit function.
		std::cerr << "Could not open file.";
		return;

	}

	//Create temp variable to store Room information
	Room temp;

	//While the file has not reached the end...
	while (!my_file.eof()) {

		//Read the file into the temp room
		temp.read_from_file(my_file);

		//If the file has not reach the end, insert the room to the tree.
		if (my_file) hotel.insert(temp);

	}

	//Close file when done
	my_file.close();

}

/************************************************
 *  Function to create the binary file with the room information.
 ***********************************************/
void create_hotel_file() {

	//All rooms to be added
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

	//Create and open file
	std::ofstream my_file;
	my_file.open(hotel_file_name, std::ios::binary);

	//If file has not opened...
	if (!my_file) {

		//... input error message and exit function
		std::cerr << "Could not open file";
		return;
	}

	//Write every room to the file
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

	//Close file
	my_file.close();

	return;

}

/************************************************
 *  Function to showcase the above functions.
 ***********************************************/
void predetermined_test(Hotel_AVL& hotel_rooms) {

	std::cout << "\nTesting free rooms function...";
	std::cout << "\nFinding rooms that are free on the 10th of August 2022.";

	std::set <Room> rooms_list;
	hotel_rooms.all_free_rooms_during_date(rooms_list, Date(10, 8, 2022));
	print_free_rooms(rooms_list);

	rooms_list.clear();

	std::cout << "\n\nTesting free room function...";
	std::cout << "\nOpening room 102.";

	hotel_rooms.free_a_room(102);

	std::cout << "\n\nTesting closed room inquiry...";
	std::cout << "\nCreating inquiry for closed rooms from the 10th of August 2022 until the 10th of September 2022.";

	hotel_rooms.closed_room_inquiry(rooms_list, Date(10, 8, 2022), Date(10, 9, 2022));
	create_closed_rooms_file(Date(10, 8, 2022), rooms_list);

	Room room;
	bool bed_found = false;

	std::cout << "\n\nTesting function for finding a room with the minimal amount of beds...";
	std::cout << "\nSearching for a bed with at least 1 bed.";
	hotel_rooms.find_room_min_beds(1, room, bed_found);

	if (!bed_found) std::cout << "\nNo bed found";
	else std::cout << "\nRoom with min beds: " << room.get_room_number();

	std::cout << "\n\nTesting function to close a room...";
	std::cout << "\nAttempting to close room 100";
	hotel_rooms.close_room(100, "Ss", Date(3, 3, 2022), Date(3, 4, 2022));

	std::cout << "\n\nTesting function to register a guest.";
	std::cout << "\nAttempting to register guest 'Alexander the Meh' in room 301 from the 10th of August 2022 until the 12 of August 2022.";

	hotel_rooms.register_guest(301, "Alexander the Okay", Date(10, 8, 2022), Date(12, 8, 2022), "");

	return;

}

/************************************************
 *  Function to chose an action to do with the rooms based on user choice. User can pick to either do an action or close the program.
 ***********************************************/
void work_with_file(Hotel_AVL& hotel_rooms) {

	int choice = 0;

	std::cout << "\nPlease pick what you would like to do";
	std::cout << "\n1. Register guest - register a guest into a given room.";
	std::cout << "\n2. Free rooms. Returns a list of free rooms";
	std::cout << "\n3. Free a room. Open a given room.";
	std::cout << "\n4. Closed room inquiry. For a given date, create a file containing all rooms closed for said date.";
	std::cout << "\n5. Search a room with at least x amount of beds. For a given amount of beds, find a room that has at least a certain amount of beds.";
	std::cout << " Priority is given to rooms with the least amount of beds.";
	std::cout << "\n6. Close a room. Close a room without adding a guest to said room.";
	std::cout << "\n7. Close operations.";
	std::cout << "\nChose an action: ";

	std::cin >> choice;

	switch (choice) {

	case 1: register_guest(hotel_rooms); break;
	case 2: all_free_rooms_during_date(hotel_rooms); break;
	case 3: free_room(hotel_rooms); break;
	case 4: closed_room_inquiry(hotel_rooms); break;
	case 5: find_room(hotel_rooms); break;
	case 6: close_room(hotel_rooms); break;
	case 7: return;
	default: std::cout << "\nInvalid entry.";
	}

	return work_with_file(hotel_rooms);

}

int main()
{

	create_hotel_file();
	Hotel_AVL hotel_rooms;
	read_hotel_rooms(hotel_rooms);

	int choice = 0;

	std::cout << "Would you like to see an example of how the program works[1] or you would prefer to work directly with the program[2]? \n";
	std::cin >> choice;
	
	while (choice != 1 && choice != 2) {

		std::cout << "\nInvalid entry. Please insert 1 or 2.\n";
		std::cin >> choice;

	}

	switch (choice) {

	case 1: predetermined_test(hotel_rooms); break;
	case 2: work_with_file(hotel_rooms); break;
	}

}
