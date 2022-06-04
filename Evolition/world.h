#pragma once
#include "game_object_list.h"
#include "game_object.h"

struct world final
{
public:
	world();
	~world();
	world(const world&) = delete;

	void update();
	void create(gameObject* object);

	bool is_free_cell(const world_size_type& x, const world_size_type& y) const;
	world_size_type get_index(const world_size_type& x, const world_size_type& y) const;
private:

	bool collision[world_size];
	game_object_list list;
};

