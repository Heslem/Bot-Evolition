#include "graphics_worker.h"
#include <cstdio>

#define get_index(x, y) (y * world_size_x + x)

graphics_worker::graphics_worker()
{
	for (game_type i = 0; i < world_size; ++i)
	{
		buffer[i] = '\n';
	}
}

graphics_worker::~graphics_worker()
{
}

void graphics_worker::clear_buffer()
{
	unsigned short counter = 0;
	unsigned short i = 0;

	for (; i < world_size; ++i)
	{
		if (counter == world_size_x - 1) {
			counter = 0; // i do that, because buffer must have \n, else buffer will clear \n and draw gameObjects wrong.
			continue;
		}
		else {
			buffer[i] = ' ';
			counter++;
		}
	}
}

void graphics_worker::set_pixel(const game_type& x, const game_type& y, const char& sprite)
{
	if (x < world_size_x - 2) {
		game_type index = get_index(x, y);

		if (index > -1 && index < world_size) {
			buffer[index] = sprite;
		}
	}
}

void graphics_worker::print_buffer()
{
	printf("%s", buffer);
}
