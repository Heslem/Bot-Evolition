#pragma once
#include "gameObject.h"

struct save final
{
	save();
	~save();
	void saveObjects(const std::vector<gameObject*> objects, const char* saveName);
};

