#pragma once
#include "Room_Node.h"

class Hotel_AVL
{
	Room_Node* root;

	void update(Room_Node* node);
	Room_Node* balance(Room_Node* node);

	Room_Node* leftLeftCase(Room_Node* node);
	Room_Node* leftRightCase(Room_Node* node);
	Room_Node* rightRightCase(Room_Node* node);
	Room_Node* rightLeftCase(Room_Node* node);

	Room_Node* rotateLeft(Room_Node* node);
	Room_Node* rotateRight(Room_Node* node);

	Room_Node* insert(Room_Node* tree, const Room& x);

	//register guest
	//free rooms [date]
	//free a room [room_numbeS

public:

	Hotel_AVL();
	Hotel_AVL(const Hotel_AVL& other);
	Hotel_AVL& operator=(const Hotel_AVL& other);
	~Hotel_AVL();

};

