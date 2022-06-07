#include "world.h"
#include "primitive_bot.h"
#include "save.h"
#include <iostream>
#include <Windows.h>
#include <string>

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

}

void world::update()
{
    clear_collision();

    // current_size not changing when program run. It changing only if object was deleted, but no created.
    game_type current_size = gameObjects.size();
    for (game_type i = 0; i < current_size; ++i)
    {
        collisions[get_index(gameObjects[i].position.get_x(), gameObjects[i].position.get_y())] = false;

        if (this->gameObjects[i].update(collisions)) {
            collisions[get_index(gameObjects[i].position.get_x(), gameObjects[i].position.get_y())] = true;

        }
        else {
            this->gameObjects.erase(i);
            current_size--;
        }
    }

}

void world::create(gameObject* object)
{
    collisions[get_index(object->position.get_x(), object->position.get_y())] = true;
    this->gameObjects.push_back(object);
}

void world::save_world() const
{
    save* lastSave = new save();

    lastSave->saveObjects(gameObjects, "exitSave.txt");

    delete lastSave;
}

bool world::is_busy_cell(const game_type& x, const game_type& y) const
{
    if (x < 1 || x > world_size_x - 2 ||
        y < 1 || y > world_size_y) return true;

    return collisions[get_index(x, y)];
}

bool world::is_free_cell(const game_type& x, const game_type& y) const
{
    return !is_busy_cell(x, y);
}

bool world::is_busy_cell(const vector2<game_type>& position) const
{
    return is_busy_cell(position.get_x(), position.get_y());
}

bool world::is_free_cell(const vector2<game_type>& position) const
{
    return !is_busy_cell(position.get_x(), position.get_y());
}

// Very slow thing
gameObject* world::get_game_object(const game_type& x, const game_type& y) const
{
    for (game_type i = 0; i < gameObjects.size(); ++i)
        if (gameObjects[i].position.get_x() == x && gameObjects[i].position.get_y() == y) return &gameObjects[i];

    return nullptr;
}

game_type world::get_index(const game_type& x, const game_type& y) const
{
    return y * world_size_x + x;
}

void world::clear_collision()
{
    for (game_type i = 0; i < world_size; ++i)
    {
        if (i < gameObjects.size()) {
            collisions[get_index(gameObjects[i].position.get_x(), gameObjects[i].position.get_y())] = true;
        }
        else {
            collisions[i] = false;
        }
    }
}
