#pragma once
#include "graphics_mode.h"
#include "vector2.h"

struct game_object
{
public:
	virtual void update() = 0;
	virtual const std::string get_save() const = 0;
public:

#if GRAPHICS_MODE
	game_object(char sprite);
#else
	game_object();
#endif
	virtual ~game_object();

#if GRAPHICS_MODE
	const char sprite_;
#endif

	const bool& isAlive() const { return alive; }
	void destroy();

	vector2 position;
private:
	bool alive = true;
};

