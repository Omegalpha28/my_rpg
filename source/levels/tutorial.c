/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** tutorial
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static const cstring_t LEVELS[7] = {
    "tutorial/01",
    "tutorial/02",
    "tutorial/03",
    "tutorial/04",
    "tutorial/05",
    "tutorial/06",
    "tutorial/07"
};

///////////////////////////////////////////////////////////////////////////////
void level_tutorial_actors(uint_t level)
{
    if (level == 2)
        entity_create(Assets.creatures[CREATURE_CINNAMON_RAT],
            V2F(0.0f, -225.0f));
}

///////////////////////////////////////////////////////////////////////////////
bool_t level_tutorial(void)
{
    uint_t level = Engine.level;
    sfMusic *music = find_music("i-m-hungry");

    if (level == 8)
        Engine.level = 0;
    if (level < 1 || level > 7 || !level_load(LEVELS[level - 1]))
        return (false);
    if (level == 1) {
        end_music();
        sfMusic_setVolume(music, clampf(Setting.master *
            (Setting.music / 100.0f) * 0.1f, 0.0f, 100.0f));
        sfMusic_play(music);
    }
    if (level != 1)
        level_tutorial_actors(level);
    return (true);
}
