#pragma once
#include "vector2.h"
#include "world_config.h"
#include "graphics_mode.h"

struct gameObject
{
public:
	virtual bool update(const bool buffer[]) = 0;
	virtual std::string get_save() const = 0;
public:
#if GRAPHICS_MODE == true
	gameObject(const char& sprite);
#else
	gameObject();
#endif
	~gameObject();
	gameObject(const gameObject&) = delete;

	void randomize_position();
	void destroy();

	vector2<game_type> position;
#if GRAPHICS_MODE == true
	const char sprite;
#endif
protected:
	bool alive = true;
};

