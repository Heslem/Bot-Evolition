#pragma once
#include "game_object_list.h"

struct save final
{
	save();
	~save();
	void saveObjects(const game_object_list& objects, const char* saveName);
};

