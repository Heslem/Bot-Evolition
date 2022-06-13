#include "world.h"
#include "bot.h"
#include "save.h"
#include <string>

#define get_index(x, y) (y * world_size_x + x)

world::world()
{
	for (std::size_t i = 0; i < 100; i++)
	{
		bot* b = new bot(*this);
		b->position = vector2::random();
		create(*b);
	}
	save_world();
}

world::~world()
{
}

void world::update()
{
	clear_collision();
	for (std::size_t i = 0; i < this->game_objects.size(); ++i)
	{
		this->game_objects[i]->update();

		if (!this->game_objects[i]->isAlive()) {
			delete this->game_objects[i];
			this->game_objects.erase(this->game_objects.begin() + i);
		}
	}
	if (this->steps > this->next_steps_to_save) {
		save_world();

		this->count_saves++;
		this->next_steps_to_save += save_interval;
	}
	else this->steps++;
}

const bool world::is_busy_cell(const game_type& x, const game_type& y) const
{
	if (x < 1 || x > world_size_x - 2 ||
		y < 1 || y > world_size_y) return true;

	return collisions[get_index(x, y)];
}

const bool world::is_free_cell(const game_type& x, const game_type& y) const
{
	return !is_busy_cell(x, y);
}

const bool world::is_busy_cell(const vector2& position) const
{
	return is_busy_cell(position.get_x(), position.get_y());
}

const bool world::is_free_cell(const vector2& position) const
{
	return !is_busy_cell(position.get_x(), position.get_y());
}

const size_t world::get_index_game_object(const game_type& x, const game_type& y) const
{
	for (size_t i = 0; i < game_objects.size(); ++i) {
		if (game_objects[i]->position.get_x() == x && game_objects[i]->position.get_y() == y) return i;
	}
	return -1;
}

void world::save_world() const
{
	save current_save;

	std::string name = ("save_" + std::to_string(count_saves) + ".botworld");

	current_save.save_objects(game_objects, name.c_str());
}

void world::create(game_object& object)
{
	this->collisions[get_index(object.position.get_x(), object.position.get_y())] = true;
	this->game_objects.push_back(&object);
}

void world::clear_collision()
{
	for (game_type i = 0; i < world_size; ++i)
	{
		this->collisions[i] = false;
	}
	for (size_t i = 0; i < game_objects.size(); ++i)
	{
		this->collisions[get_index(game_objects[i]->position.get_x(), game_objects[i]->position.get_y())] = true;
	}
}
