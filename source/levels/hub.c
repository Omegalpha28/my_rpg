/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** hub
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
bool_t level_hub(void)
{
    if (Engine.level != 0 || !level_load("shared/ub"))
        return (false);
    effect("firethrower", V2F(-91.0f, -439.0f), false);
    effect("firethrower", V2F(91.0f, -439.0f), false);
    return (true);
}
