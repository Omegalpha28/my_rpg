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
bool_t level_tutorial(void)
{
    uint_t level = Engine.level;

    if ((level < 1 && level > 7) || !level_load(LEVELS[level - 1]))
        return (false);
    return (true);
}
