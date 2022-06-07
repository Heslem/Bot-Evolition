#pragma once
#include <vector>
#include "graphics_mode.h"
#include "gameObject.h"
#include "game_object_list.h"
#include "world_config.h"

constexpr unsigned long long save_interval = 500;

struct world final
{
	world();
	~world();
	void update();
	void create(gameObject* object);
	void save_world();

	const bool is_busy_cell(const game_type& x, const game_type& y) const;
	const bool is_free_cell(const game_type& x, const game_type& y) const;

	const bool is_busy_cell(const vector2<game_type>& position) const;
	const bool is_free_cell(const vector2<game_type>& position) const;

	gameObject* get_game_object(const game_type& x, const game_type& y) const;

	const game_type get_index(const game_type& x, const game_type& y) const;

	const bool is_full() const { return gameObjects.is_full(); };

#if GRAPHICS_MODE
	game_object_list gameObjects;
#endif

private:
	unsigned long long count_saves = 0;
	unsigned long long next_steps_to_save;
	unsigned long long steps;

	void clear_collision();

#if GRAPHICS_MODE == false
	game_object_list gameObjects;
#endif
	bool collisions[world_size];
};

