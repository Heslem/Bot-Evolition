#include "world.h"
#include "primitive_bot.h"
#include "save.h"
#include <iostream>
#include <Windows.h>
#include <string>

world::world()  
{
    for (size_t i = 0; i < world_size; i++)
    {
        collisions[i] = false;
    }
    for (int i = 0; i < 100; i++)
    {
        primitive_bot* object = new primitive_bot(*this);

        object->randomizeBrain();
        object->randomize_position();

        this->create(object);
    }

    save_world();
}

world::~world()
{

}

void world::update()
{
    clear_collision();

    static world_size_type current_size = gameObjects.size();
    
    for (register world_size_type i = 0; i < current_size; ++i)
    {
        collisions[get_index(gameObjects[i].position.x, gameObjects[i].position.y)] = false;

        if (this->gameObjects[i].update(collisions)) {
            collisions[get_index(gameObjects[i].position.x, gameObjects[i].position.y)] = true;
        }
        else {
            this->gameObjects.erase(i);
            current_size--;
        }
    }

    //std::string cmd = "title " + std::to_string(gameObjects.size());
    //system(cmd.c_str());
}

void world::create(gameObject* object)
{
    collisions[get_index(object->position.x, object->position.y)] = true;
    this->gameObjects.push_back(object);
}

void world::save_world() const
{
    save* lastSave = new save();

    lastSave->saveObjects(gameObjects, "exitSave.txt");

    delete lastSave;
}

bool world::is_busy_cell(const world_size_type& x, const world_size_type& y) const
{
    if (x < 1 || x > world_size_x - 2 ||
        y < 1 || y > world_size_y) return true;

    return collisions[get_index(x, y)];
}

bool world::is_free_cell(const world_size_type& x, const world_size_type& y) const
{
    return !is_busy_cell(x, y);
}

bool world::is_busy_cell(const vector2<world_size_type>& position) const
{
    return is_busy_cell(position.x, position.y);
}

bool world::is_free_cell(const vector2<world_size_type>& position) const
{
    return !is_busy_cell(position.x, position.y);
}

world_size_type world::get_index(const world_size_type& x, const world_size_type& y) const
{
    return y * world_size_x + x;
}

void world::clear_collision()
{
    for (register world_size_type i = 0; i < world_size; ++i)
    {
        if (i < gameObjects.size()) {
            collisions[get_index(gameObjects[i].position.x, gameObjects[i].position.y)] = true;
        }
        else {
            collisions[i] = false;
        }
    }
}
