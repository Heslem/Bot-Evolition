#include "world.h"
#include "primitive_bot.h"

world::world()
{
    for (size_t i = 0; i < 10; i++)
    {
        primitive_bot* object = new primitive_bot();
        object->randomizeBrain();
        object->setPosition(vector2<int>(1, 3));


        this->create(object);
    }
    
    
}

world::~world()
{
    for (size_t i = 0; i < this->gameObjects.size(); i++)
    {
        delete this->gameObjects[i];
    }
}

void world::update()
{
    for (size_t i = 0; i < this->gameObjects.size(); i++)
    {
        this->gameObjects[i]->update();

        if (!this->gameObjects[i]->isAlive()) {
            this->gameObjects.erase(this->gameObjects.begin() + i);
        }
    }
}

void world::create(gameObject* object)
{
    this->gameObjects.push_back(object);
}
