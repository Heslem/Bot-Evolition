#pragma once
typedef short brain_type;

constexpr brain_type BRAIN_SIZE = 24;
constexpr brain_type MAX_COMMAND = 9; // count of real command

constexpr game_type MAX_AGE_STEPS = 9000;
constexpr game_type CHANGE_EVOLITION = 16;
constexpr game_type FOOD_WHEN_START = 400;
constexpr game_type D_CHANGE_EVOLITION = CHANGE_EVOLITION / 2;
constexpr game_type FOOD_FOR_CREATE_NEW_BOT = 600;
constexpr game_type FOOD_FROM_LIGHT = 2;
constexpr game_type LIGHT_LEVEL = 10;
constexpr game_type MAX_FOOD = 1000;
constexpr game_type FOOD_FOR_KILL = 100;
constexpr game_type WALK_COST = 4;
constexpr game_type ATTACK_COST = 60; // if bot don't kill bot, he loss attack cost