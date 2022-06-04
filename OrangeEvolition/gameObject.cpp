#include "gameObject.h"
gameObject::gameObject(const char& sprite) : sprite(sprite)
{
	
}

gameObject::~gameObject()
{
}

const void gameObject::move(const vector2<int>& movement)
{
	position = position + movement;
	if (position.x > world_size_x) position.x = world_size_x;
	else if (position.x < 0) position.x = 0;

	if (position.y > world_size_y) position.y = world_size_y;
	else if (position.y < 0) position.y = 0;
}

const void gameObject::randomize_position()
{
	//TODO: write code
}
