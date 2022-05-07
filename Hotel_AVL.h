#pragma once
#include "Room_Node.h"

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

	//void register_guest();

	//register guest
	//free rooms [date]
	//free a room [room_number]
	//free room inquiry [date, date]
	//find room [beds]
	//close room [note]

public:

	Hotel_AVL();
	Hotel_AVL(const Hotel_AVL& other);
	Hotel_AVL& operator=(const Hotel_AVL& other);
	~Hotel_AVL();

};

