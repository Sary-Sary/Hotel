#pragma once
#include "Room.h"

struct Room_Node
{
	Room room; /**< Room corresponding to the node */
	Room_Node* left; /**< Node to the left of the current node */
	Room_Node* right; /**< Node to the right of the current node */

	int height; /**< Height of the current subtree */
	int bf; /**< Balance factor of the current subtree. For an AVL, bf must be == {0, 1}. */

	Room_Node(const Room& room_) {

		room = room_;
		left = nullptr;
		right = nullptr;

		height = 1;
		bf = 0;

	}

};

