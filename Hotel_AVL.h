#pragma once
#include "Room_Node.h"
#include <list>

class Hotel_AVL
{
	Room_Node* root;
	 
	void update(Room_Node* node);
	Room_Node* balance(Room_Node* node);

	Room_Node* left_left_case(Room_Node* node);
	Room_Node* left_right_case(Room_Node* node);
	Room_Node* right_right_case(Room_Node* node);
	Room_Node* right_left_case(Room_Node* node);

	Room_Node* rotate_left(Room_Node* node);
	Room_Node* rotate_right(Room_Node* node);

	Room_Node* insert(Room_Node* tree, const Room& new_room);
	
	void free(Room_Node* tree);
	Room_Node* clone(Room_Node* tree);

	bool register_guest(Room_Node* tree, int room_number, std::string name, Date start_date, Date end_date, std::string note);
	void all_free_rooms_during_date(std::list <Room>& free_rooms, Room_Node* tree, Date date);
	bool free_a_room(Room_Node* tree, int room_number);
	void closed_room_inquiry(Room_Node* tree, std::list <Room>& taken_rooms, Date start_date, Date end_date);
	void find_room_min_beds
			(Room_Node* tree, int current_min_amount_of_beds, const int min_amount_of_beds_needed, Room& room, bool& at_least_one_room_was_found);
	bool close_room(Room_Node* tree, const int room_number, const std::string note, const Date start_date, const Date end_date);

	void max_beds(Room_Node* tree, int& max_amount_of_beds);

	//free room inquiry [date, date]

public:

	Hotel_AVL();
	Hotel_AVL(const Hotel_AVL& other);
	Hotel_AVL& operator=(const Hotel_AVL& other);
	~Hotel_AVL();

	void insert(const Room& new_room);

	bool register_guest(int room_number, std::string name, Date start_date, Date end_date, std::string note);
	void all_free_rooms_during_date(std::list <Room>& free_rooms, Date date);
	bool free_a_room(int room_number);
	void closed_room_inquiry(std::list <Room>& taken_rooms, Date start_date, Date end_date);
	void find_room_min_beds(const int min_amount_of_beds_needed, Room& room, bool& at_least_one_room_was_found);
	bool close_room(const int room_number, const std::string note, const Date start_date, const Date end_date);

};


