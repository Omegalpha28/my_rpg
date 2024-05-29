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
    for (uint_t i = 0; i < (uint_t)(clamp(Engine.level - 9, 1, 5)); i++)
        entity_create(Assets.creatures[get_creature()],
            V2F(0.0f, -225.0f));
}

///////////////////////////////////////////////////////////////////////////////
static void init_crab_boss_room(void)
{
    sfMusic *song = find_music("crab-boss");

    entity_create(Assets.creatures[CREATURE_CRAB_BOSS], V2F(50.0f, -150.0f));
    end_music();
    sfMusic_setVolume(song, clampf(Setting.master * (Setting.music / 100.0f) *
        0.1f, 0.0f, 100.0f));
    sfMusic_play(song);
}

///////////////////////////////////////////////////////////////////////////////
bool_t level_biome1(void)
{
    if (Engine.level < 10 || Engine.level > 19)
        return (false);
    level_load(Engine.level != 19 ? LEVELS[rand() % LEVEL_COUNT] :
        "boss/crab");
    if (Engine.level != 19)
        use_spawner();
    else
        init_crab_boss_room();
    sfView_move(Win.view, V2F(0.0f, -125.0f));
    sfRenderWindow_setView(Win.self, Win.view);
    return (true);
}
