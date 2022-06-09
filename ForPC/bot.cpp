#include "bot.h"
#include <random>
#include <string>

#if GRAPHICS_MODE
bot::bot(world& my_world) : game_object('B'), current_world(my_world), food(FOOD_WHEN_START)
{
	randomize_brain();
}
#else
bot::bot(world& my_world) : current_world(my_world), food(FOOD_WHEN_START)
{
	randomize_brain();
}
#endif
bot::~bot()
{
}

#if GRAPHICS_MODE
bot::bot(const bot& copy_bot) : game_object('B'), current_world(copy_bot.current_world), food(FOOD_WHEN_START)
{
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = copy_bot.brain[i];
	}
	evolition();
}
#else
bot::bot(const bot& copy_bot) : current_world(copy_bot.current_world), food(FOOD_WHEN_START)
{
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = copy_bot.brain[i];
	}
	evolition();
}
#endif

bot& bot::operator=(const bot& right_bot)
{
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = right_bot.brain[i];
	}
	this->food = right_bot.food;
	this->current_world = right_bot.current_world;
	this->counter = right_bot.counter;
	this->position = right_bot.position;

	return *this;
}

void bot::update()
{
	if (food <= 0) destroy();
	else food--;

	if (counter == BRAIN_SIZE - 1) { counter = 0; }

	type_brain command = brain[counter];
	switch (command)
	{
	case 1: // move -x
		if (current_world.is_free_cell(this->position.get_x() - 1, this->position.get_y()))
			position.set_x(this->position.get_x() - 1);

		break;
	case 2: // move +x
		if (current_world.is_free_cell(this->position.get_x() + 1, this->position.get_y()))
			position.set_x(this->position.get_x() + 1);

		break;

	case 3: // move +y
		if (current_world.is_free_cell(this->position.get_x(), this->position.get_y() + 1))
			position.set_y(this->position.get_y() + 1);

		break;

	case 4: // move -y
		if (current_world.is_free_cell(this->position.get_x(), this->position.get_y() - 1))
			position.set_y(this->position.get_y() - 1);

		break;

	case 5: // spawn new bot
		if (food > 500) {
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

			vector2 positionBot = vector2(x, y);
			if (positionBot.get_x() != x || position.get_y() != y) break;

			if (current_world.is_free_cell(positionBot)) {
				bot* sub_bot = new bot(*this);

				sub_bot->position = positionBot;
				current_world.create(*sub_bot);

				food -= 500;
			}
		}
		break;
	case 7:
		if (food < 1000 && position.get_y() < 10) { food += 20; }
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
			(x < world_size - 1 && x > 2) ||
			(y < world_size_y - 1 && y > 2);

		if (x == this->position.get_x() && y == this->position.get_y()) killBot = false;

		if (killBot &&
			current_world.is_busy_cell(x, y))
		{
			game_type index = current_world.get_index_game_object(x, y);
			if (index != -1) {
				current_world.game_objects[index]->destroy();
				food += 400;
			}
		}

		break;
	}

	counter++;
	steps++;
	if (steps > MAX_AGE_STEPS) {
		destroy();
	}
}

const std::string bot::get_save() const
{
	std::string brainData("");
	for (unsigned char i = 0; i < BRAIN_SIZE; i++) {
		brainData.append("{" + std::to_string(brain[i]) + "}");
	}

	return std::string("bot: ") + "\n" +
		"x: " + std::to_string(position.get_x()) + "\n" +
		"y: " + std::to_string(position.get_y()) + "\n" +
		"food: " + std::to_string(food) + "\n" +
		"brain: " + brainData.c_str();
}

static std::random_device device;
static std::mt19937 rng(device());

static std::uniform_int_distribution<std::mt19937::result_type> c_evo(1, MAX_COMMAND);
static std::uniform_int_distribution<std::mt19937::result_type> change_evo(0, CHANGE_EVOLITION);
static std::uniform_int_distribution<std::mt19937::result_type> b_evo(0, BRAIN_SIZE - 1);


void bot::randomize_brain()
{
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		brain[i] = c_evo(rng);
	}
}

void bot::evolition()
{
	if (change_evo(rng) == D_CHANGE_EVOLITION) {
		brain[b_evo(rng)] = c_evo(rng);
	}
}
