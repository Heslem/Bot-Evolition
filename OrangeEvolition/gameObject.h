#pragma once
#include "vector2.h"
#include "world_config.h"

class gameObject
{
public:
	virtual void update() = 0;

public:
	gameObject(const char& sprite);
	~gameObject();
	gameObject(const gameObject&) = delete;

	const void move(const  vector2<int>& movement);
	const void randomize_position();

	const void setPosition(const vector2<int>& position) { this->position = position; }
	const vector2<int> getPosition(void) const { return this->position; }
	const char& getSprite() const { return this->sprite;  }
	const void setSprite(const char& sprite) { this->sprite = sprite; }
	const bool isAlive() const { return this->alive; }
	const void destroy() { this->alive = false; }
private:
	vector2<int> position;
	char sprite;
	bool alive = true;
};

