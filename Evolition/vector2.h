#pragma once
#include "world_config.h"

struct vector2
{
public:

	world_size_type x;
	world_size_type y;

	vector2();
	vector2(const world_size_type& x, const world_size_type& y);

	void set_position(const world_size_type& x, const world_size_type& y);
};

