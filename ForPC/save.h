#pragma once
#include "game_list.h"

struct save
{
	save();
	~save();
	void saveObjects(const game_list& objects, const std::string& saveName);
};

