#pragma once
#include "world.h"

typedef short brain_type;

constexpr brain_type BRAIN_SIZE = 16;
constexpr brain_type MAX_COMMAND = 8; // count of real command

constexpr game_type MAX_AGE_STEPS = 2000;
constexpr game_type CHANGE_EVOLITION = 10;
constexpr game_type FOOD_WHEN_START = 400;
constexpr game_type D_CHANGE_EVOLITION = CHANGE_EVOLITION / 2;

class bot final :
	public game_object
{
public:
	bot(world& my_world);
	~bot();
	bot(const bot& copy_bot);
	bot& operator=(const bot& right_bot);

	void update() override;
	const std::string get_save() const override;

	void randomize_brain();
	void evolition();
private:
	world& current_world;

	brain_type brain[BRAIN_SIZE];

	brain_type counter = 0;
	game_type steps = 0;
	game_type food;
};

