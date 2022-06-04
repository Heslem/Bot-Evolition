#pragma once
#include "game_object.h"
#include "world_config.h"

struct game_object_list final
{
public:
	game_object_list();
	~game_object_list();
	game_object_list(const game_object_list&) = delete;

	void push_back(gameObject* gameObject);
	void erase(const world_size_type& i);

	world_size_type size() const { return pointer; };
	bool is_full() const { return pointer == world_size - 1; }

	gameObject& operator[](world_size_type i) { return *data[i]; }

private:
	void move_left(const world_size_type& offset);

	gameObject* data[world_size];
	world_size_type pointer;
};

