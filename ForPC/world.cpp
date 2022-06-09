#include "world.h"
#include "primitive_bot.h"
#include "save.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

world::world()
{
    for (game_type i = 0; i < 50; i++)
    {
        primitive_bot* object = new primitive_bot(*this);
        object->randomize_position();

        this->create(object);
    }

    save_world();
}

world::~world()
{
    save_world();
}

void world::update()
{
    clear_collision();

    for (game_type i = 0; i < gameObjects.size(); ++i)
    {
        if (this->gameObjects[i]->update()) {
            collisions[get_index(gameObjects[i]->position.get_x(), gameObjects[i]->position.get_y())] = true;
        }
        else {
            delete this->gameObjects.at(i);
            this->gameObjects.erase(this->gameObjects.begin() + i);
        }
    }

    if (steps > next_steps_to_save) {
        save_world();
        next_steps_to_save += save_interval;
    }
    else steps++;
   /* std::string str("title " + std::to_string(current_size));
    system(str.c_str());*/
}

void world::create(gameObject* object)
{
    collisions[get_index(object->position.get_x(), object->position.get_y())] = true;
    this->gameObjects.push_back(object);
}

void world::save_world()
{
    save current_save;

    std::string name = ("save_" + std::to_string(count_saves) + ".botworld");
    
    current_save.saveObjects(gameObjects, name.c_str());

    count_saves++;
}

const bool world::is_busy_cell(const game_type& x, const game_type& y) const
{
    if (x < 1 || x > world_size_x - 2 ||
        y < 1 || y > world_size_y) return true;

    return collisions[get_index(x, y)];
}

const bool world::is_free_cell(const game_type& x, const game_type& y) const
{
    return !is_busy_cell(x, y);
}

const bool world::is_busy_cell(const vector2<game_type>& position) const
{
    return is_busy_cell(position.get_x(), position.get_y());
}

const bool world::is_free_cell(const vector2<game_type>& position) const
{
    return !is_busy_cell(position.get_x(), position.get_y());
}

// Very slow thing
gameObject* world::get_game_object(const game_type& x, const game_type& y) const
{
    for (game_type i = 0; i < gameObjects.size(); ++i) {
        if (gameObjects[i]->position.get_x() == x && gameObjects[i]->position.get_y() == y) return gameObjects[i];
    }
    return nullptr;
}

const game_type world::get_index(const game_type& x, const game_type& y) const
{
    return y * world_size_x + x;
}

void world::clear_collision()
{
    memset(collisions, false, world_size); // set all elements of array false

    for (game_type i = 0; i < gameObjects.size(); i++)
    {
        collisions[get_index(gameObjects[i]->position.get_x(), gameObjects[i]->position.get_y())] = true;
    }
}
