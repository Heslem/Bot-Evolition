#pragma once
#include "gameObject.h"

#define brain_size 10

class primitive_bot :
    public gameObject
{
public:
    primitive_bot();
    ~primitive_bot();
    primitive_bot(const primitive_bot&) = delete;

    void update() override;
    void randomizeBrain();
private:
    unsigned char brain[brain_size]; // bytes brain
    const unsigned char max_command = 4; 
    unsigned char counter = 0;
    int food = 100000;
};

