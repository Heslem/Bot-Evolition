#pragma once
#include "gameObject.h"
#include "world.h"

typedef unsigned char type_brain;

constexpr type_brain BRAIN_SIZE = 12;
constexpr type_brain MAX_COMMAND = 6;

constexpr unsigned short CHANGE_EVOLITION = 10;
constexpr unsigned short FOOD_WHEN_START = 400;
constexpr unsigned short D_CHANGE_EVOLITION = CHANGE_EVOLITION / 2;

struct primitive_bot final:
    public gameObject
{
public:
    primitive_bot(world& mainWorld);
    ~primitive_bot();
    primitive_bot(const primitive_bot& bot);

    bool update(const bool buffer[]) override;
    std::string get_save() const override;
    void randomizeBrain();
    void evolition();
private:
    type_brain brain[BRAIN_SIZE];

    world& mainWorld;
    type_brain counter = 0;
    short food = 0;
};

