#pragma once
#include "Room.h"

struct Room_Node
{
	Room room;
	Room* left;
	Room* right;

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

