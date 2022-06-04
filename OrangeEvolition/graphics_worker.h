#pragma once
#include <stdio.h>
#include "vector2.h"
#include "gameObject.h"
#include <vector>

#define clear_screen() printf("\033[H\033[J")
#define buffer_size_x 16
#define buffer_size_y 16
#define BUFFER_SIZE (buffer_size_x * buffer_size_y)

char buffer[buffer_size];

void clear_buffer(const char& symbol) {

	unsigned short counter = 0;
	for (size_t i = 0; i < buffer_size; i++)
	{
		if (counter == buffer_size_x - 1) {
			buffer[i] = '\n';
			counter = 0;
		}
		else {
			buffer[i] = symbol;
			counter++;
		}
	}
}

void buffer_set_pixel(const int& x, const int& y, const char& symbol) {
	if (x > buffer_size_x - 1 || y > buffer_size_y) return;

	unsigned int index = y * buffer_size_x + x;
	buffer[index] = symbol;
}

const void buffer_set_pixel(vector2<int> position, const char& symbol) {
	buffer_set_pixel(position.x, position.y, symbol);
}

const void buffer_draw_gameObject(const gameObject& object) {
	buffer_set_pixel(object.getPosition(), object.getSprite());
}

void buffer_draw_gameObjects(const std::vector<gameObject*> gameObjects) {
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		buffer_draw_gameObject(*gameObjects[i]);
	}
}

void print_buffer(void) {
	printf(buffer);
}