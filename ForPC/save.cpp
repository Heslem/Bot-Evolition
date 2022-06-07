#include "save.h"
#include <iostream>
#include <fstream>

save::save()
{
}

save::~save()
{
}

void save::saveObjects(const game_object_list& objects, const char* saveName)
{
	std::ofstream outfile;
	outfile.open(saveName, std::ofstream::out | std::ofstream::trunc);

	for (game_type i = 0; i < objects.size(); ++i)
	{
		outfile << objects[i].get_save().c_str() << std::endl << "end." << std::endl;
	}
	 
	outfile.close();
}
