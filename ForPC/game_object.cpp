#include "game_object.h"

#if GRAPHICS_MODE
game_object::game_object(char sprite) : sprite_(sprite)
{
}
#else
game_object::game_object()
{
}
#endif

game_object::~game_object()
{
}

void game_object::destroy()
{
	this->alive = false;
}
