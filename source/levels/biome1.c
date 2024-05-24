/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** biome1
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static const uint_t LEVEL_COUNT = 4;

static const cstring_t LEVELS[] = {
    "tutorial/02",
    "tutorial/03",
    "tutorial/04",
    "tutorial/05",
    NULL
};

///////////////////////////////////////////////////////////////////////////////
static int get_creature(void)
{
    int rdx = rand() % CREATURE_COUNT;

    while (rdx == CREATURE_DUMMY || rdx == CREATURE_CRAB_BOSS ||
        rdx == CREATURE_SIGN_BOSS || rdx == CREATURE_PLAYER ||
        rdx == CREATURE_PNJ || rdx == CREATURE_CHEST)
        rdx = rand() % CREATURE_COUNT;
    return (rdx);
}

///////////////////////////////////////////////////////////////////////////////
static void use_spawner(void)
{
    entity_create(Assets.creatures[get_creature()],
        V2F(0.0f, -225.0f));
    entity_create(Assets.creatures[get_creature()],
        V2F(0.0f, -225.0f));
}

///////////////////////////////////////////////////////////////////////////////
bool_t level_biome1(void)
{
    if (Engine.level < 10 || Engine.level > 19)
        return (false);
    level_load(LEVELS[rand() % LEVEL_COUNT]);
    use_spawner();
    return (true);
}
