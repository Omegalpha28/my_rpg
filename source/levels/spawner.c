/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** spawner
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

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

float randomf(int min, int max)
{
    int tmp = min;

    if (min > max) {
        min = max;
        max = tmp;
    }
    return ((float)(rand() % (max - min - 1) + min));
}

///////////////////////////////////////////////////////////////////////////////
static v2f_t get_spawn_location(void)
{
    return (V2F(randomf(-125, 125), randomf(-230, -200)));
}

///////////////////////////////////////////////////////////////////////////////
void use_spawner(uint_t n)
{
    for (uint_t i = 0; i < n; i++) {
        entity_create(Assets.creatures[get_creature()],
            get_spawn_location());
    }
}
