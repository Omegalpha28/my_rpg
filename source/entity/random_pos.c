/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** random_pos
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
v2f_t rand_pos(v2f_t origin, int min_range, int max_range)
{
    float length = (float)(rand() % (max_range - min_range)) + min_range;

    origin.x = (rand() % 2) ? origin.x + length : origin.x - length;
    origin.y = (rand() % 2) ? origin.y + length : origin.y - length;
    return (origin);
}

///////////////////////////////////////////////////////////////////////////////
v2f_t flee_rand_pos(v2f_t origin, int min_range, int max_range)
{
    float length = (float)(rand() % (max_range - min_range)) + min_range;

    if (rand() % 2)
        origin.x = (rand() % 2) ? origin.x + length : origin.x - length;
    else
        origin.y = (rand() % 2) ? origin.y + length : origin.y - length;
    return (origin);
}
