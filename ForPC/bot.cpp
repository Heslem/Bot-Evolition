#include "bot.h"
#include <random>
#include <string>

#if GRAPHICS_MODE
bot::bot(world& my_world) : game_object('B'), current_world(my_world), food(FOOD_WHEN_START)
{
	randomize_brain();

	// start data of brain, it's need because bot's quick die without it

	brain[0] = 7;
	brain[1] = 7;
	brain[2] = 7;
	brain[3] = 5;
	brain[4] = 2;

	generate_id();
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
bot::bot(const bot& copy_bot) : game_object('B'), current_world(copy_bot.current_world), food(FOOD_WHEN_START), id(copy_bot.id)
{
	for (brain_type i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = copy_bot.brain[i];
	}
	evolition();
}
#else
bot::bot(const bot& copy_bot) : current_world(copy_bot.current_world), food(FOOD_WHEN_START), id(copy_bot.id)
{
	for (type_brain i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = copy_bot.brain[i];
	}
	evolition();
}
#endif

bot& bot::operator=(const bot& right_bot)
{
	for (brain_type i = 0; i < BRAIN_SIZE; ++i) {
		this->brain[i] = right_bot.brain[i];
	}
	this->food = right_bot.food;
	this->current_world = right_bot.current_world;
	this->counter = right_bot.counter;
	this->position = right_bot.position;
	this->id = right_bot.id;

	return *this;
}

void bot::update()
{
	if (food <= 0) destroy();

	brain_type command = brain[counter];
	if (command < MAX_COMMAND) {
		// move left
		if (command == 1) { // move -x
			if (current_world.is_free_cell(this->position.get_x() - 1, this->position.get_y())) {
				position.set_x(this->position.get_x() - 1);
			}
			food--;
		}
		// move right
		else if (command == 2) { // move +x
			if (current_world.is_free_cell(this->position.get_x() + 1, this->position.get_y()))
				position.set_x(this->position.get_x() + 1);

			food--;
		}
		// move down
		else if (command == 3) { // move +y
			if (current_world.is_free_cell(this->position.get_x(), this->position.get_y() + 1))
				position.set_y(this->position.get_y() + 1);

			food--;
		}
		// move up
		else if (command == 4) { // move -y
			if (current_world.is_free_cell(this->position.get_x(), this->position.get_y() - 1))
				position.set_y(this->position.get_y() - 1);

			food--;
		}
		// spawn new bot command
		else if (command == 5) { // spawn new bot
			if (food > FOOD_FOR_CREATE_NEW_BOT) {
				bool create = true;

				increase_counter();

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
				if (create) {

					vector2 positionBot = vector2(x, y);
					if (positionBot.get_x() == x || position.get_y() == y) {

						if (current_world.is_free_cell(positionBot)) {
							bot* sub_bot = new bot(*this);

							sub_bot->position = positionBot;
							current_world.create(*sub_bot);

							food -= FOOD_FOR_CREATE_NEW_BOT;
						}
					}
				}
			}
		}
		// kill bot command
		else if (command == 6) {
			increase_counter();
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
			else food -= ATTACK_COST;

			if (killBot &&
				current_world.is_busy_cell(x, y))
			{
				game_type index = current_world.get_index_game_object(x, y);
				if (index != -1) {
					current_world.game_objects[index]->destroy();
					food += FOOD_FOR_KILL;
				}
			}

		} // kill
		// get food from light command
		else if (command == 7) { // get food
			if (food < MAX_FOOD && position.get_y() < LIGHT_LEVEL) { food += FOOD_FROM_LIGHT; }

			/*if (food < 1000 && position.get_y() < light_level) {
				food += light_level - position.get_y();
			}*/
		}
		// goto command
		else if (command == 8) { // goto
			increase_counter();
			counter = brain[counter] - 1;
		}
		// if command
		else if (command == 9) {
			increase_counter();
			brain_type conditionType = brain[counter];
			increase_counter();
			bool result = getConditionResult(conditionType);

			brain_type end_counter = brain[counter];

			if (!result) {
				counter = end_counter;
			}

		}
	}

	increase_counter();

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
		"id: " + std::to_string(id) + "\n" + 
		"x: " + std::to_string(position.get_x()) + "\n" +
		"y: " + std::to_string(position.get_y()) + "\n" +
		"food: " + std::to_string(food) + "\n" +
		"brain: " + brainData;
}

const game_type bot::get_id() const
{
	return id;
}

static std::random_device device;
static std::mt19937 rng(device());

static std::uniform_int_distribution<std::mt19937::result_type> c_evo(1, BRAIN_SIZE);
static std::uniform_int_distribution<std::mt19937::result_type> change_evo(0, CHANGE_EVOLITION);
static std::uniform_int_distribution<std::mt19937::result_type> b_evo(0, BRAIN_SIZE - 1);


void bot::randomize_brain()
{
	for (brain_type i = 0; i < BRAIN_SIZE; ++i) {
		brain[i] = c_evo(rng);
	}
}

void bot::evolition()
{
	if (change_evo(rng) == D_CHANGE_EVOLITION) {
		brain[b_evo(rng)] = c_evo(rng);
		generate_id();
	}
}

void bot::increase_counter()
{
	if (counter > BRAIN_SIZE - 1) 
		counter = 0; 
	else 
		counter++;
}

void bot::generate_id()
{
	id = 0;
	for (game_type i = 0; i < BRAIN_SIZE; i++)
	{
		id += (game_type)brain[i];
	}
}

const bool bot::getConditionResult(const game_type& conditionType) const
{
	bool result = false;

	if (conditionType == 1) {
		int x = this->position.get_x() - 1;
		int y = this->position.get_y();

		if (current_world.is_busy_cell(x, y)) {
			result = current_world.get_index_game_object(x, y) != -1;
		}
	}
	else if (conditionType == 2) {
		int x = this->position.get_x() + 1;
		int y = this->position.get_y();

		if (current_world.is_busy_cell(x, y)) {
			result = current_world.get_index_game_object(x, y) != -1;
		}
	}
	else if (conditionType == 3) {
		int x = this->position.get_x();
		int y = this->position.get_y() + 1;

		if (current_world.is_busy_cell(x, y)) {
			result = current_world.get_index_game_object(x, y) != -1;
		}
	}
	else if (conditionType == 4) {
		int x = this->position.get_x();
		int y = this->position.get_y() - 1;

		if (current_world.is_busy_cell(x, y)) {
			result = current_world.get_index_game_object(x, y) != -1;
		}
	}

	return result;
}
