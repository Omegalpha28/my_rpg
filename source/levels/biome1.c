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
static const uint_t LEVEL_COUNT = 6;

///////////////////////////////////////////////////////////////////////////////
static const cstring_t LEVELS[] = {
    "tutorial/02",
    "tutorial/03",
    "tutorial/04",
    "tutorial/05",
    "tutorial/06",
    "tutorial/07",
    NULL
};

///////////////////////////////////////////////////////////////////////////////
static void init_crab_boss_room(void)
{
    sfMusic *song = find_music("crab-boss");

    entity_create(Assets.creatures[CREATURE_CRAB_BOSS], V2F(50.0f, -150.0f));
    end_music();
    sfMusic_setVolume(song, clampf(Setting.master * (Setting.music / 100.0f) *
        0.7f, 0.0f, 100.0f));
    sfMusic_play(song);
}

///////////////////////////////////////////////////////////////////////////////
static void set_biome1_music(void)
{
    sfMusic *music = find_music("i-m-hungry");

    end_music();
    sfMusic_setVolume(music, clampf(Setting.master *
        (Setting.music / 100.0f) * 0.1f, 0.0f, 100.0f));
    sfMusic_play(music);
}

///////////////////////////////////////////////////////////////////////////////
bool_t level_biome1(void)
{
    if (Engine.level < 10 || Engine.level > 19)
        return (false);
    level_load(Engine.level != 19 ? LEVELS[rand() % LEVEL_COUNT] :
        "boss/crab");
    if (Engine.level == 10)
        set_biome1_music();
    if (Engine.level != 19)
        use_spawner((uint_t)(clamp(Engine.level - 9, 1, 5)));
    else
        init_crab_boss_room();
    sfView_move(Win.view, V2F(0.0f, -125.0f));
    sfRenderWindow_setView(Win.self, Win.view);
    return (true);
}
