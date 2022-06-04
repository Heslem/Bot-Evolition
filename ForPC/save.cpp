#include "save.h"
#include <iostream>
#include <fstream>

save::save()
{
}

save::~save()
{
}

void save::saveObjects(const game_list& objects, const std::string& saveName)
{
	std::ofstream outfile;
	outfile.open(saveName.c_str(), std::ofstream::out | std::ofstream::trunc);

	for (register world_size_type i = 0; i < objects.size(); ++i)
	{
		outfile << objects[i].get_save().c_str() << std::endl << "end." << std::endl;
	}
	 
	outfile.close();
}
