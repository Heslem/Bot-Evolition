#pragma once
#include "graphics_mode.h"
#if GRAPHICS_MODE

#include "game_object.h"
#include "world_config.h"
#include "vector2.h"

#define clear_screen() printf("\033[H\033[J")

struct graphics_worker final
{
public:
	graphics_worker();
	~graphics_worker();
	graphics_worker(const graphics_worker&) = delete;

	void clear_buffer();
	void set_pixel(const game_type& x, const game_type& y, const char& sprite);
	void print_buffer();
private:

	char buffer[world_size];
};

#endif