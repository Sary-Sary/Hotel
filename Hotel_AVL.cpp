#include "Hotel_AVL.h"

/************************************************
*	Default constructor.	
*	Creates a nullptr root.
 ***********************************************/
Hotel_AVL::Hotel_AVL() : root(nullptr) {}

/************************************************
*	Destructor. 
	Frees each node from a tree.
 ***********************************************/
Hotel_AVL::~Hotel_AVL() {

	free(root);

}

/************************************************
*	Function to free a tree.
*	Recursively goes through a tree, deleting leaves until there are no nodes left.
 ***********************************************/
void Hotel_AVL::free(Room_Node* tree) {

	//If a node is not a nullptr...
	if (tree) {

		//... call free on its left and right node before deleting the node.
		free(tree->left);
		free(tree->right);
		delete tree;

	}

	//Set node as a nullptr
	tree = nullptr;
	return;

}

/************************************************
*	Function to update tree.
*	Updates tree when a new node has been added. Changes the height of the tree and the balance factor.
 ***********************************************/
void Hotel_AVL::update(Room_Node* tree) {

	if (tree == nullptr) return;

	//Get the height of the left and right tree
	int left_height = (tree->left == nullptr) ? 0 : tree->left->height;
	int right_height = (tree->right == nullptr) ? 0 : tree->right->height;

	//Update height and the balance factor
	tree->height = 1 + std::max(left_height, right_height);
	tree->bf = right_height - left_height;

}

//Diagrams from https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

/************************************************
*	Function for left rotation.
*	Rebalances a tree.
* 	  y                                x
*    / \                             /  \
*   x   T3                          T1   y 
*  / \       < - - - - - - -            / \
* T1  T2     Left Rotation            T2  T3
 ***********************************************/
Room_Node* Hotel_AVL::rotate_left(Room_Node* node) {

	Room_Node* new_parent = node->right;
	node->right = new_parent->left;
	new_parent->left = node;

	update(node);
	update(new_parent);

	return new_parent;

}

/************************************************
*	Function for right rotation.
*	Rebalances a tree.
*     y                           x
*    / \     Right Rotation     /  \
*   x   T3   - - - - - - - >   T1   y 
*  / \                             / \
* T1  T2                          T2  T3
 ***********************************************/
Room_Node* Hotel_AVL::rotate_right(Room_Node* node) {

	Room_Node* new_parent = node->left;
	node->left = new_parent->right;
	new_parent->right = node;

	update(node);
	update(new_parent);

	return new_parent;

}


/************************************************
*	Function to balance tree when if a left-left case.
*         z                                      y 
*        / \                                   /   \
*       y   T4      Right Rotate (z)          x      z
*      / \          - - - - - - - - ->      /  \    /  \ 
*     x   T3                               T1  T2  T3  T4
*    / \
*  T1   T2
 ***********************************************/
Room_Node* Hotel_AVL::left_left_case(Room_Node* node) {

	return rotate_right(node);

}


/************************************************
*	Function to balance tree when in left-right case.
*     z                               z                           x
*    / \                            /   \                        /  \ 
*   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
*  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
*T1   x                          y    T3                    T1  T2 T3  T4
*    / \                        / \
*  T2   T3                    T1   T2
 ***********************************************/
Room_Node* Hotel_AVL::left_right_case(Room_Node* node) {

	node->left = rotate_left(node->left);
	return left_left_case(node);

}

/************************************************
*	Function to balance tree when in right-right case.
*  z                                y
* /  \                            /   \ 
*T1   y     Left Rotate(z)       z      x
*    /  \   - - - - - - - ->    / \    / \
*   T2   x                     T1  T2 T3  T4
*       / \
*     T3  T4
 ***********************************************/
Room_Node* Hotel_AVL::right_right_case(Room_Node* node) {

	return rotate_left(node);

}

/************************************************
*	Function to balance tree when in right-left case.
*   z                            z                            x
*  / \                          / \                          /  \ 
*T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
*    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
*   x   T4                      T2   y                  T1  T2  T3  T4
*  / \                              /  \
*T2   T3                           T3   T4
 ***********************************************/
Room_Node* Hotel_AVL::right_left_case(Room_Node* node) {

	node->right = rotate_right(node->right);
	return right_right_case(node);

 }

/************************************************
*	Function to balance a tree.
 ***********************************************/
Room_Node* Hotel_AVL::balance(Room_Node* node) {

	//If node is empty, tree is balance
	if (node == nullptr) return nullptr;

	//If the balance factor is -2...
	if (node->bf == -2) {

		//... check left node's balance factor and chose a case.
		if (node->left->bf <= 0) return left_left_case(node);
		return left_right_case(node);

	}

	//Else if the balance factor is 2...
	else if (node->bf == 2) {

		//... check right's node balance factor and chose a case.
		if (node->right->bf >= 0) return right_right_case(node);
		return right_left_case(node);

	}

	return node;

}

/************************************************
*	Function to insert a node.
 ***********************************************/
Room_Node* Hotel_AVL::insert(Room_Node* tree, const Room& new_room) {

	//If a node is empty, add the room to the node
	if (tree == nullptr) return new Room_Node(new_room);

	//Checks if the current node's room is bigger or smaller than the room we wish to insert and traverse accordingly
	if (tree->room < new_room) tree->right = insert(tree->right, new_room);
	else tree->left = insert(tree->left, new_room);

	//Update tree when done and balance the tree
	update(tree);
	return balance(tree);

}

/************************************************
*	Public function to accept the new room and insert it into the tree.
 ***********************************************/
void Hotel_AVL::insert(const Room& new_room) {

	root = insert(root, new_room);
	return;
}

/************************************************
*	Function to find the room where the guest should be registrated in.
 ***********************************************/
bool Hotel_AVL::register_guest(Room_Node* node, int room_number, std::string guest_name, Date start_date, Date end_date, std::string note) {

	//If we reach an empty node, return that the room was not found
	if (node == nullptr) return false;

	//If the current room node corresponds to the room number we are looking for...
	if (node->room == room_number) {

		//Register the guest to said room
		node->room.register_new_guest(guest_name, start_date, end_date,note);
		return true;
	}

	//If the current room node has a larger number than the seeked room's number, go left down the tree
	if (node->room > room_number) return register_guest(node->left, room_number, guest_name, start_date, end_date, note);
	//Else go right
	return register_guest(node->right, room_number, guest_name, start_date, end_date, note);

}

/************************************************
*	Public function to accept the new guest and register them.
 ***********************************************/
bool Hotel_AVL::register_guest(int room_number, std::string name, Date start_date, Date end_date, std::string note) {

	return register_guest(root, room_number, name, start_date, end_date, note);

}

/************************************************
*	Function to find all open rooms for a given date.
 ***********************************************/
void Hotel_AVL::all_free_rooms_during_date(std::set <Room>& all_free_rooms, Room_Node* tree, Date date) {

	//If the node is empty, return
	if (tree == nullptr) return;

	//If the room is open...
	if (tree->room.get_is_room_closed() == false) {

		//... add room to the set, then continue traversal to the left and right.
		all_free_rooms.insert(tree->room);
		all_free_rooms_during_date(all_free_rooms, tree->left, date);
		all_free_rooms_during_date(all_free_rooms, tree->right, date);
		return;

	}

	//If the room is taken during the date...
	if (tree->room.get_start_date() < date && tree->room.get_end_date() > date) {

		//... traverse to the left and right.
		all_free_rooms_during_date(all_free_rooms, tree->left, date);
		all_free_rooms_during_date(all_free_rooms, tree->right, date);
		return;

	}

	//Else, add the room to the set, then continue traversal to the left and right.
	all_free_rooms.insert(tree->room);
	all_free_rooms_during_date(all_free_rooms, tree->left, date);
	all_free_rooms_during_date(all_free_rooms, tree->right, date);
	return;

}

/************************************************
*	Public function to find all free rooms for a given day.
 ***********************************************/
void Hotel_AVL::all_free_rooms_during_date(std::set <Room>& free_rooms, Date date) {

	return all_free_rooms_during_date(free_rooms, root, date);
}

/************************************************
*	Function to find a room to be freed.
 ***********************************************/
bool Hotel_AVL::free_a_room(Room_Node* tree, int room_number) {

	//If node is empty, return room not found
	if (tree == nullptr) return false;

	//If room is found...
	if (tree->room == room_number) {

		//... attempt to free room.
		tree->room.free_room();
		return true;

	}

	//Else, check if current room is larger or smaller than the seeked for room and traverse left or right respectively
	if (tree->room > room_number) return free_a_room(tree->left, room_number);
	return free_a_room(tree->right, room_number);

}


/************************************************
*	Public function to find a room with a specific room number.
 ***********************************************/
bool Hotel_AVL::free_a_room(int room_number) {

	return free_a_room(root, room_number);

}

/************************************************
*	Function to find the max amount of beds in a room.
 ***********************************************/
void Hotel_AVL::max_beds(Room_Node* tree, int& max_amount_of_beds) {

	//If room is empty, return
	if (tree == nullptr) return;

	//If the current amount of beds in a room is larger than the current max amount of beds...
	if (tree->room.get_amount_of_beds() > max_amount_of_beds) {

		//... update the max amount of beds
		max_amount_of_beds = tree->room.get_amount_of_beds();

	}

	//Continue traversal to the left and the right
	max_beds(tree->left, max_amount_of_beds);
	max_beds(tree->right, max_amount_of_beds);
	return;

}

/************************************************
*	Public function to find a free room with at least x beds.
 ***********************************************/
void Hotel_AVL::find_room_min_beds
		(Room_Node* tree, int current_min_amount_of_beds, const int min_amount_of_beds_needed, Room& room, bool& at_least_one_room_was_found) {

	//If node is empty, return
	if (tree == nullptr) return;

	//If a room is closed...
	if (tree->room.get_is_room_closed() == true) {

		//... traverse to the left and right and return
		find_room_min_beds(tree->left, current_min_amount_of_beds, min_amount_of_beds_needed, room, at_least_one_room_was_found);
		find_room_min_beds(tree->right, current_min_amount_of_beds, min_amount_of_beds_needed, room, at_least_one_room_was_found);
		return;

	}

	//Else, if the room has >= than the needed minimum amount of beds...
	if (tree->room.get_amount_of_beds() >= min_amount_of_beds_needed) {

		//... check if the saved room has less than the current max amount of beds in a room...
		if (tree->room.get_amount_of_beds() < current_min_amount_of_beds) {

			//... if yes, update the amount and confirm a room has been found fullfiling the requirements
			at_least_one_room_was_found = true;
			current_min_amount_of_beds = tree->room.get_amount_of_beds();
			room = tree->room;
		}

	}
	
	//Traverse to the left and right
	find_room_min_beds(tree->left, current_min_amount_of_beds, min_amount_of_beds_needed, room, at_least_one_room_was_found);
	find_room_min_beds(tree->right, current_min_amount_of_beds, min_amount_of_beds_needed, room, at_least_one_room_was_found);
	return;
}


/************************************************
*	Public function to find a room with at least x beds.
 ***********************************************/
void Hotel_AVL::find_room_min_beds(const int min_amount_of_beds_needed, Room& room, bool& at_least_one_room_was_found) {

	//Find the max amount of beds in a room. This ensures we can find a bed that has at least a given amount of beds, as long
	//as we later check that it is free
	int current_min_amount_of_beds = 0;
	max_beds(root, current_min_amount_of_beds);

	return find_room_min_beds(root, current_min_amount_of_beds, min_amount_of_beds_needed, room, at_least_one_room_was_found);

}

/************************************************
*	Function to close a room.
 ***********************************************/
bool Hotel_AVL::close_room(Room_Node* tree, const int room_number, const std::string note, const Date start_date, const Date end_date) {

	//If a node is empty, return
	if (tree == nullptr) return false;

	//If a room is equal to the room number we were looking for
	if (tree->room == room_number) {

		//Close the room and return
		tree->room.close_room(note, start_date, end_date);
		return true;
	}

	//Traverse to the left and right
	if (tree->room > room_number) return close_room(tree->left, room_number, note, start_date, end_date);
	return close_room(tree->right, room_number, note, start_date, end_date);
}

/************************************************
*	Public function to close a room and add a note.
 ***********************************************/
bool Hotel_AVL::close_room(const int room_number, const std::string note, const Date start_date, const Date end_date) {

	return close_room(root, room_number, note, start_date, end_date);

}

/************************************************
*	Function to create a closed room inquiry.
 ***********************************************/
void Hotel_AVL::closed_room_inquiry(Room_Node* tree, std::set <Room>& taken_rooms, Date start_date, Date end_date) {

	//If a node is empty, return
	if (tree == nullptr) return;

	//If a room is closed for the period we are looking for, add it to the set of closed rooms
	if (tree->room.room_is_closed_for_period(start_date, end_date)) taken_rooms.insert(tree->room);

	//Traverse to the left and right
	closed_room_inquiry(tree->left, taken_rooms, start_date, end_date);
	closed_room_inquiry(tree->right, taken_rooms, start_date, end_date);

	return;
}

/************************************************
*	Public function to commence a closed room inquiry.
 ***********************************************/
void Hotel_AVL::closed_room_inquiry(std::set <Room>& taken_rooms, Date start_date, Date end_date) {

	return closed_room_inquiry(root, taken_rooms, start_date, end_date);

}