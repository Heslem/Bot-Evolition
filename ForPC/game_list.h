#pragma once
#include "world_config.h"
#include "gameObject.h"


struct game_list final
{
public:
	game_list();
	~game_list();
	game_list(const game_list&) = delete;

	void push_back(gameObject* gameObject);
	void erase(const world_size_type& i);

	world_size_type size() const { return pointer; };
	bool is_full() const { return pointer == world_size - 1; }

	gameObject& operator[](world_size_type i) const { return *data[i]; }
private:
	void move_left(const world_size_type& offset);

	gameObject* data[world_size];
	world_size_type pointer; 
};

