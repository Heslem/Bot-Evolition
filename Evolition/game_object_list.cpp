#include "game_object_list.h"

game_object_list::game_object_list() : pointer(0)
{
	for (world_size_type i = 0; i < world_size; ++i)
		this->data[i] = nullptr;
}

game_object_list::~game_object_list()
{
	for (world_size_type i = 0; i < pointer; ++i)
		delete this->data[i];
}

void game_object_list::push_back(gameObject* gameObject)
{
	if (is_full()) return;

	this->data[pointer] = gameObject;
	this->pointer++;
}

void game_object_list::erase(const world_size_type& i)
{
	if (i >= this->pointer) return;

	if (i != pointer)
		move_left(i);
	else
		this->data[i] = nullptr;

	this->pointer--;
}

void game_object_list::move_left(const world_size_type& offset)
{
	register int j = offset;
	for (; j < pointer; ++j)
		this->data[j] = this->data[j + 1];
	this->data[j] = nullptr;
}