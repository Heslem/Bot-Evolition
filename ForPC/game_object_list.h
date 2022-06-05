#pragma once
#include "world_config.h"
#include "gameObject.h"

// I create this list, because i thinking what vector slow for my project. game_object_list capacity limited by world_size

struct game_object_list final
{
public:
	game_object_list();
	~game_object_list();
	game_object_list(const game_object_list&) = delete;

	void push_back(gameObject* gameObject);
	void erase(const game_type& i);

	game_type size() const { return pointer; };
	bool is_full() const { return pointer == world_size - 1; }

	gameObject& operator[](game_type i) const { return *data[i]; }
private:
	void move_left(const game_type& offset);

	gameObject* data[world_size];
	game_type pointer; 
};

