#pragma once
#include "graphics_mode.h"

#if GRAPHICS_MODE == true

#include <stdio.h>
#include "vector2.h"
#include "gameObject.h"
#include <vector>
#include "game_list.h"
#include "world_config.h"

#define clear_screen() printf("\033[H\033[J")

static char buffer[world_size];

static void buffer_init() {
	for (register game_type i = 0; i < world_size; ++i)
		buffer[i] = '\n';
}

static void buffer_clear(const char& symbol = ' ') {

	unsigned char counter = 0;
	register unsigned short i = 0;

	for (; i < world_size; ++i)
	{
		if (counter == world_size_x - 1) {
			counter = 0;
			continue;
		}
		else {
			buffer[i] = symbol;
			counter++;
		}
	}
}

static void buffer_set_pixel(const int& x, const int& y, const char& symbol) {
	if (x > world_size_x - 2 || x < 0 || y > world_size_y || y < 0) return;

	game_type index = y * world_size_x + x;
	buffer[index] = symbol;
}

static const void buffer_set_pixel(vector2<game_type> position, const char& symbol) {
	buffer_set_pixel(position.x, position.y, symbol);
}

static const void buffer_draw_gameObject(const gameObject& object) {
	buffer_set_pixel(object.position, object.sprite);
}

static void buffer_draw_gameObjects(game_object_list& gameObjects) {
	for (register game_type i = 0; i < gameObjects.size(); ++i)
		buffer_set_pixel(gameObjects[i].position, gameObjects[i].sprite);
}


static void print_buffer() {
	printf(buffer);
}
#endif //GRAPHICS_MODE