#pragma once
#include <vector>

#include "gameObject.h"

class world
{
public:
	world();
	~world();
	void update();
	void create(gameObject* object);

	std::vector<gameObject*> gameObjects;
};

