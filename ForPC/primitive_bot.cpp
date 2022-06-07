#include "primitive_bot.h"
#include <random>
#include <iostream>
#include <string>
#include "buffer_config.h"
#include "world_config.h"

#if GRAPHICS_MODE
primitive_bot::primitive_bot(world& mainWorld) : gameObject('B'), food(FOOD_WHEN_START), mainWorld(mainWorld)
{
	randomizeBrain();
}
#else
primitive_bot::primitive_bot(world& mainWorld) : food(FOOD_WHEN_START), mainWorld(mainWorld)
{
	randomizeBrain();
}
#endif
#include <Windows.h>
primitive_bot::~primitive_bot()
{
}

#if GRAPHICS_MODE
primitive_bot::primitive_bot(const primitive_bot& bot) : gameObject('B'), food(FOOD_WHEN_START), mainWorld(bot.mainWorld)
{
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = bot.brain[i];
	}
	evolition();
}
primitive_bot& primitive_bot::operator=(const primitive_bot& bot)
{
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = bot.brain[i];
	}
	this->food = bot.food;
	this->mainWorld = bot.mainWorld;
	this->counter = bot.counter;
	this->position = bot.position;

	return *this;
}
#else
primitive_bot::primitive_bot(const primitive_bot& bot) : food(FOOD_WHEN_START), mainWorld(bot.mainWorld)
{
	type_brain i = 0;
	for (; i < BRAIN_SIZE; ++i)
	{
		this->brain[i] = bot.brain[i];
	}
	evolition();
}
#endif

bool primitive_bot::update()
{
	if (food <= 0) { destroy(); }
	else { food--; }

	if (position.get_y() < 8) { food += 40; }
	if (counter == BRAIN_SIZE) { counter = 0; }

	type_brain command = brain[counter];
	switch (command)
	{
	case 1: // move -x
		if (mainWorld.is_free_cell(this->position.get_x() - 1, this->position.get_y())) 
			position.set_x(this->position.get_x() - 1);

		break;
	case 2: // move +x
		if (mainWorld.is_free_cell(this->position.get_x() + 1, this->position.get_y())) 
			position.set_x(this->position.get_x() + 1);

		break;

	case 3: // move +y
		if (mainWorld.is_free_cell(this->position.get_x(), this->position.get_y() + 1)) 
			position.set_y(this->position.get_y() + 1);

		break;

	case 4: // move -y
		if (mainWorld.is_free_cell(this->position.get_x(), this->position.get_y() - 1)) 
			position.set_y(this->position.get_y() - 1);

		break;

	case 5: // spawn new bot
		if (food > 500 && !mainWorld.is_full()) {
			bool create = true;
			counter++;

			int x = this->position.get_x();
			int y = this->position.get_y();

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

			vector2<game_type> positionBot = vector2<game_type>(x, y);
			if (positionBot.get_x() != x || position.get_y() != y) break;

			if (mainWorld.is_free_cell(positionBot)) {
				primitive_bot* bot = new primitive_bot(*this);

				bot->position = positionBot;
				mainWorld.create(bot);
				food -= 500;
			}
		}
		break;

	case 6: // kill
		counter++;
		game_type x = this->position.get_x();
		game_type y = this->position.get_y();
		//getting side
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
		}

		bool killBot = false;
		killBot = 
			(x < world_size - 1 && x > 2 ) ||
			(y < world_size_y - 1 && y > 2);

		if (x == this->position.get_x() && y == this->position.get_y()) killBot = false;

		if (killBot &&
			mainWorld.is_busy_cell(x, y)) 
		{
			gameObject* object = mainWorld.get_game_object(x, y);
			if (object != nullptr)
			{
				object->destroy();
				food += 400;
			}
		}

		break;
	}

	counter++;

	return alive;
}

std::string primitive_bot::get_save() const
{
	std::string brainData("");
	for (unsigned char i = 0; i < BRAIN_SIZE; i++) {
		brainData.append(std::to_string(brain[i]));
	}

	return std::string("bot: ") + "\n" +
		"x: " + std::to_string(position.get_x()) + "\n" +
		"y: " + std::to_string(position.get_y()) + "\n" +
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
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		brain[i] = c_evo(rng);
	}
}

void primitive_bot::evolition()
{
	if (change_evo(rng) == D_CHANGE_EVOLITION) {
		brain[b_evo(rng)] = c_evo(rng);
	}
}


