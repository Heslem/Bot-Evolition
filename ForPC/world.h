#pragma once
#include "game_object.h"
#include <vector>
#include "vector2.h"
#include "graphics_mode.h"

constexpr unsigned long long save_interval = 50000;

struct world final
{
public:
	world();
	~world();
	void update();
	void create(game_object& object);

	const bool is_busy_cell(const game_type& x, const game_type& y) const;
	const bool is_free_cell(const game_type& x, const game_type& y) const;

	const bool is_busy_cell(const vector2& position) const;
	const bool is_free_cell(const vector2& position) const;
	const game_type get_index_game_object(const game_type& x, const game_type& y) const;

	void save_world() const;

	std::vector<game_object*> game_objects;
private:
	unsigned long count_saves = 0;
	unsigned long next_steps_to_save = save_interval;
	unsigned long steps = 0;

	void clear_collision();
	bool collisions[world_size];
};

