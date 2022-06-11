#pragma once
#include "world.h"
#include "bot_config.h"

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
	const game_type get_id() const override;

	void randomize_brain();
	void evolition();

	void increase_counter();
private:
	void generate_id();
	const bool getConditionResult(const game_type& conditionType) const;

	world& current_world;

	brain_type brain[BRAIN_SIZE];

	brain_type counter = 0;
	game_type steps = 0;
	game_type food;
	game_type id = 0;
};

