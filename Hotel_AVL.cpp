#include "Hotel_AVL.h"

Room_Node* Hotel_AVL::clone(Room_Node* tree)
{
	if (tree == nullptr)
	{
		return nullptr;
	}

	Room_Node* cloned = new Room_Node(tree->room);
	cloned->left = clone(tree->left);
	cloned->right = clone(tree->right);
	return cloned;
}

Hotel_AVL::Hotel_AVL() : root(nullptr) {}

Hotel_AVL::Hotel_AVL(const Hotel_AVL& other) : root(nullptr) {

	root = clone(other.root);

}

Hotel_AVL& Hotel_AVL::operator=(const Hotel_AVL& other) {

	if (this != &other) {

		free(root);
		root = clone(other.root);

	}

	return *this;

}

Hotel_AVL::~Hotel_AVL() {

	free(root);

}

void Hotel_AVL::free(Room_Node* tree) {

	if (tree) {

		free(tree->left);
		free(tree->right);
		delete tree;

	}

	tree = nullptr;
	return;

}

void Hotel_AVL::update(Room_Node* tree) {

	if (tree == nullptr) return;

	int left_height = (tree->left == nullptr) ? 0 : tree->left->height;
	int right_height = (tree->right == nullptr) ? 0 : tree->right->height;

	tree->height = 1 + std::max(left_height, right_height);
	tree->bf = right_height - left_height;

}


Room_Node* Hotel_AVL::rotate_left(Room_Node* node) {

	Room_Node* new_parent = node->right;
	node->right = new_parent->left;
	new_parent->left = node;

	update(node);
	update(new_parent);

	return new_parent;

}

Room_Node* Hotel_AVL::rotate_right(Room_Node* node) {

	Room_Node* new_parent = node->left;
	node->left = new_parent->right;
	new_parent->right = node;

	update(node);
	update(new_parent);

	return new_parent;

}

Room_Node* Hotel_AVL::left_left_case(Room_Node* node) {

	return rotate_right(node);

}
Room_Node* Hotel_AVL::left_right_case(Room_Node* node) {

	node->left = rotate_left(node->left);
	return left_left_case(node);

}
Room_Node* Hotel_AVL::right_right_case(Room_Node* node) {

	return rotate_left(node);

}
Room_Node* Hotel_AVL::right_left_case(Room_Node* node) {

	node->right = rotate_right(node->right);
	return right_right_case(node);

}

Room_Node* Hotel_AVL::balance(Room_Node* node) {

	if (node == nullptr) return nullptr;

	if (node->bf == -2) {

		if (node->left->bf <= 0) return left_left_case(node);
		return left_right_case(node);

	}

	else if (node->bf == 2) {

		if (node->right->bf >= 0) return right_right_case(node);
		return right_left_case(node);

	}

	return node;

}

Room_Node* Hotel_AVL::insert(Room_Node* tree, const Room& new_room) {

	if (tree == nullptr) return new Room_Node(new_room);

	if (tree->room < new_room) tree->right = insert(tree->right, new_room);
	else tree->left = insert(tree->left, new_room);

	update(tree);
	return balance(tree);

}

bool Hotel_AVL::register_guest(Room_Node* node, int room_number, std::string guest_name, Date start_date, Date end_date, std::string note) {

	if (node == nullptr) return false;

	if (node->room == room_number) {

		node->room.register_new_guest(guest_name, start_date, end_date,note);
		return true;
	}

	if (node->room > room_number) return register_guest(node->left, room_number, guest_name, start_date, end_date, note);
	return register_guest(node->right, room_number, guest_name, start_date, end_date, note);

}

void Hotel_AVL::all_free_rooms_during_date(std::list <Room>& all_free_rooms, Room_Node* tree, Date date) {

	if (tree == nullptr) return;

	if (tree->room.get_is_room_closed() == false) {

		all_free_rooms_during_date(all_free_rooms, tree->left, date);
		all_free_rooms_during_date(all_free_rooms, tree->right, date);
		return;

	}

	if (tree->room.get_start_date() < date && tree->room.get_end_date() > date) {

		all_free_rooms_during_date(all_free_rooms, tree->left, date);
		all_free_rooms_during_date(all_free_rooms, tree->right, date);
		return;

	}

	all_free_rooms.push_back(tree->room);
	all_free_rooms_during_date(all_free_rooms, tree->left, date);
	all_free_rooms_during_date(all_free_rooms, tree->right, date);
	return;

}

bool Hotel_AVL::free_a_room(Room_Node* tree, int room_number) {

	if (tree == nullptr) return;

	if (tree->room == room_number) {

		tree->room.free_room();
		return true;

	}

	if (tree->room > room_number) return free_a_room(tree->left, room_number);
	return free_a_room(tree->right, room_number);

}

void Hotel_AVL::max_beds(Room_Node* tree, int& max_amount_of_beds) {

	if (tree == nullptr) return;

	if (tree->room.get_amount_of_beds() > max_amount_of_beds) {

		max_amount_of_beds = tree->room.get_amount_of_beds();

	}

	max_beds(tree->left, max_amount_of_beds);
	max_beds(tree->right, max_amount_of_beds);
	return;

}

void Hotel_AVL::find_room(Room_Node* tree, int current_min_amount_of_beds, const int min_amount_of_beds_needed, Room& room) {

	if (tree == nullptr) return;

	if (tree->room.get_amount_of_beds() >= min_amount_of_beds_needed) {

		if (tree->room.get_amount_of_beds() < current_min_amount_of_beds) {

			current_min_amount_of_beds = tree->room.get_amount_of_beds();
			room = tree->room;
		}

	}

	find_room(tree->left, current_min_amount_of_beds, min_amount_of_beds_needed, room);
	find_room(tree->right, current_min_amount_of_beds, min_amount_of_beds_needed, room);
	return;
}

bool Hotel_AVL::close_room(Room_Node* tree, const int room_number, const std::string note, const Date start_date, const Date end_date) {

	if (tree == nullptr) return false;

	if (tree->room == room_number) {

		tree->room.close_room(note, start_date, end_date);
		return true;
	}

	if (tree->room > room_number) return close_room(tree->left, room_number, note, start_date, end_date);
	return close_room(tree->right, room_number, note, start_date, end_date);

}