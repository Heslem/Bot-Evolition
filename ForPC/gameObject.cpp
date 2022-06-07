#include "gameObject.h"
#include "world_config.h"

#if GRAPHICS_MODE == true
gameObject::gameObject(const char& sprite) : sprite(sprite)
{
	
}
#else
gameObject::gameObject()
{
}
#endif

gameObject::~gameObject()
{
}

void gameObject::randomize_position()
{
	position = position.random(world_size_x, world_size_y);
}

void gameObject::destroy()
{
	this->alive = false;
}
