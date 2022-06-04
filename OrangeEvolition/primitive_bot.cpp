#include "primitive_bot.h"
#include <random>
#include <iostream>

primitive_bot::primitive_bot() : gameObject('B')
{
}

primitive_bot::~primitive_bot()
{
}

void primitive_bot::update()
{
	if (counter > sizeof(brain)) counter = 0;

	if (brain[counter] == 1) {
		move(vector2<int>(-1, 0));
	}
	else if (brain[counter] == 2) {
		move(vector2<int>(1, 0));
	}
	else if (brain[counter] == 3) {
		move(vector2<int>(0, 1));
	}
	else if (brain[counter] == 4) {
		move(vector2<int>(0, -1));
	}
	if (food < 0) destroy();
	else food--;

	counter++;
}

void primitive_bot::randomizeBrain()
{
	for (size_t i = 0; i < sizeof(this->brain); i++)
	{
		 unsigned char value = 1 + rand() % max_command;
		 brain[i] = value;
	}
}
