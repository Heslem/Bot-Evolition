#pragma once
#include "world.h"
#include "vector2.h"
#include "world.h"

struct gameObject
{
public:
	virtual void update() = 0;
public:
	gameObject();
	~gameObject();
	gameObject(const gameObject&) = delete;

	vector2 position;

};

