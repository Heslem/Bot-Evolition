#pragma once
#include "gameObject.h"
#include "world.h"

typedef unsigned char type_brain;

constexpr type_brain BRAIN_SIZE = 16;
constexpr type_brain MAX_COMMAND = 7;

constexpr game_type MAX_AGE_STEPS = 2000;
constexpr game_type CHANGE_EVOLITION = 10;
constexpr game_type FOOD_WHEN_START = 400;
constexpr game_type D_CHANGE_EVOLITION = CHANGE_EVOLITION / 2;

struct primitive_bot final:
    public gameObject
{
public:
    primitive_bot(world& mainWorld);
    ~primitive_bot();
    primitive_bot(const primitive_bot& bot);
    primitive_bot& operator=(const primitive_bot& bot);

    bool update() override;
    std::string get_save() const override;
    void randomizeBrain();
    void evolition();
private:
    type_brain brain[BRAIN_SIZE];
    
    world& mainWorld;
    type_brain counter = 0;

    game_type food = 0;
    game_type steps = 0;
};

