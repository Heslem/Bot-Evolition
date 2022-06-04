#include "world.h"

world::world() {

}

world::~world() {

}

void world::update() {

}

void world::create(gameObject* object)
{
	collision[get_index(object->position.x, object->position.y)] = true;
}

bool world::is_free_cell(const world_size_type& x, const world_size_type& y) const
{
	return collision[get_index(x, y)];
}

world_size_type world::get_index(const world_size_type& x, const world_size_type& y) const
{
	if (x < 0 || x > world_size_x || y < 0 || y > world_size_y) return 0;

	return (y * world_size_x + x);
}
