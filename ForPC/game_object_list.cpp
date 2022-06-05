#include "game_object_list.h"
#include <iostream>

game_object_list::game_object_list() : pointer(0)
{
	register game_type i = 0;
	for (; i < world_size; ++i)
		this->data[i] = nullptr;
}

game_object_list::~game_object_list()
{
	for (game_type i = 0; i < pointer; ++i)
		delete this->data[i];
}

void game_object_list::push_back(gameObject* gameObject)
{
	if (is_full()) return;

	this->data[pointer] = gameObject;
	this->pointer++;
}

void game_object_list::erase(const game_type& i)
{
	if (i < this->pointer) {

		if (i != pointer) {
			move_left(i);
		}
		else {
			delete this->data[i];
			this->data[i] = nullptr;
		}

		this->pointer--;

	}
}

void game_object_list::move_left(const game_type& offset)
{
	register game_type j = offset;
	for (; j < pointer; ++j)
	{
		this->data[j] = this->data[j + 1];
	}

	delete this->data[j];
	this->data[j] = nullptr; // i delete data[j], and after set it to nullptr. I don't know this good for memory, or this BIG mistake.
}
