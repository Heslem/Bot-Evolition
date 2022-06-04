#include "primitive_bot.h"
#include <random>
#include <iostream>
#include <string>
#include "buffer_config.h"
#include "world_config.h"

#if GRAPHICS_MODE
primitive_bot::primitive_bot(world& mainWorld) : gameObject('B'), food(FOOD_WHEN_START), mainWorld(mainWorld)
{
	
}
#else
primitive_bot::primitive_bot(world& mainWorld) : food(FOOD_WHEN_START), mainWorld(mainWorld)
{
}
#endif

primitive_bot::~primitive_bot()
{
}

#if GRAPHICS_MODE
primitive_bot::primitive_bot(const primitive_bot& bot) : gameObject('B'), food(FOOD_WHEN_START), mainWorld(bot.mainWorld)
{
	for (register type_brain i = 0; i < BRAIN_SIZE; ++i)
		this->brain[i] = bot.brain[i];
	evolition();
}
#else
primitive_bot::primitive_bot(const primitive_bot& bot) : food(FOOD_WHEN_START), mainWorld(bot.mainWorld)
{
	register type_brain i = 0;
	for (; i < BRAIN_SIZE; ++i)
	{
		this->brain[i] = bot.brain[i];
	}
	evolition();
}
#endif

bool primitive_bot::update(const bool buffer[])
{
	if (position.y < 8) food += 5;

	if (food < 0) return false;
	else food--;

	if (counter == BRAIN_SIZE) counter = 0;

	switch (brain[counter])
	{
	case 1:
		if (mainWorld.is_free_cell(this->position.x - 1, this->position.y)) position.set_x(this->position.x - 1);

		break;
	case 2:
		if (mainWorld.is_free_cell(this->position.x + 1, this->position.y)) position.set_x(this->position.x + 1);

		break;

	case 3:
		if (mainWorld.is_free_cell(this->position.x, this->position.y + 1)) position.set_y(this->position.y + 1);

		break;

	case 4:
		if (mainWorld.is_free_cell(this->position.x, this->position.y - 1)) position.set_y(this->position.y - 1);

		break;

	case 5:
		if (food > 500 && !mainWorld.is_full()) {
			bool create = true;
			counter++;

			int x = this->position.x;
			int y = this->position.y;

			switch (brain[counter])
			{
			case 1:
				x--;
				break;
			case 2:
				x++;
				break;

			case 3:
				y++;
				break;

			case 4:
				y--;
				break;
			default:
				create = false;
				break;
			}
			if (!create) break;

			vector2<world_size_type> positionBot = vector2<world_size_type>(x, y);
			if (positionBot.x != x || position.y != y) break;

			if (mainWorld.is_free_cell(positionBot)) {
				primitive_bot* bot = new primitive_bot(*this);

				bot->position = positionBot;
				mainWorld.create(bot);
				food -= 500;
			}
		}
		break;
	}

	counter++;

	return true;
}

std::string primitive_bot::get_save() const
{
	std::string brainData("");
	for (unsigned char i = 0; i < BRAIN_SIZE; i++)
		brainData.append(std::to_string(brain[i]));

	return std::string("bot: ") + "\n" +
		"x: " + std::to_string(position.x) + "\n" +
		"y: " + std::to_string(position.y) + "\n" +
		"food: " + std::to_string(food) + "\n" +
		"brain: " + brainData.c_str();
}

static std::random_device device;
static std::mt19937 rng(device());

static const std::uniform_int_distribution<std::mt19937::result_type> c_evo(1, MAX_COMMAND);
static const std::uniform_int_distribution<std::mt19937::result_type> change_evo(0, CHANGE_EVOLITION);
static const std::uniform_int_distribution<std::mt19937::result_type> b_evo(0, BRAIN_SIZE - 1);

void primitive_bot::randomizeBrain()
{
	for (register type_brain i = 0; i < BRAIN_SIZE; ++i)
		brain[i] = c_evo(rng);
}

void primitive_bot::evolition()
{
	if (change_evo(rng) == D_CHANGE_EVOLITION)
		brain[b_evo(rng)] = c_evo(rng);
}


