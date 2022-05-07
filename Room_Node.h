#pragma once
#include "Room.h"

struct Room_Node
{
	Room room;
	Room_Node* left;
	Room_Node* right;

	int height;
	int bf;

	Room_Node(const Room& room_) {

		room = room_;
		left = nullptr;
		right = nullptr;

		height = 1;
		bf = 0;

	}

};

