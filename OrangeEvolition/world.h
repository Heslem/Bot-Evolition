#pragma once
#include <vector>
#include "graphics_mode.h"
#include "gameObject.h"
#include "game_list.h"
#include "world_config.h"

struct world final
{
	world();
	~world();
	void update();
	void create(gameObject* object);
	void save_world() const;

	bool is_busy_cell(const game_type& x, const game_type& y) const;
	bool is_free_cell(const game_type& x, const game_type& y) const;

	bool is_busy_cell(const vector2<game_type>& position) const;
	bool is_free_cell(const vector2<game_type>& position) const;

	game_type get_index(const game_type& x, const game_type& y) const;

	bool is_full() const { return gameObjects.is_full(); };

#if GRAPHICS_MODE
	game_object_list gameObjects;
#endif
	//world_size_type size;
private:

	void clear_collision();

#if GRAPHICS_MODE == false
	game_list gameObjects;
#endif
	bool collisions[world_size];
};

