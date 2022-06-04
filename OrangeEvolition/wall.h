#pragma once
#include "gameObject.h"

class wall : 
	public gameObject
{
public:
	wall();
	~wall();
	wall(const wall&) = delete;

	void update() override;
private:
};

