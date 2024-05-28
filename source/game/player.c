/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** player
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
struct player_s Player = {
    NULL, {0.0f, 0.0f}, {0.0f, -SPEED},
    {0.0f, 0.0f}, 0, 0.0f, 0, false, {0.0f, 0.0f},
    WEAPON_RIFLE_AK, {WEAPON_RIFLE_AK, WEAPON_NO},
    {35, 0}, 23, 1.5f, 0, 0, false, 0LU, false, false, {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
    }
};
