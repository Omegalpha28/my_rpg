/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** layering
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void swap_actors(uint_t j, bool_t *swapped)
{
    actor_t *tmp = Pool.actors[j];

    if (Pool.actors[j]->position.y < Pool.actors[j + 1]->position.y)
        return;
    Pool.actors[j] = Pool.actors[j + 1];
    Pool.actors[j + 1] = tmp;
    *swapped = true;
}

///////////////////////////////////////////////////////////////////////////////
void sort_actors_pool(void)
{
    bool_t swapped = false;

    if (Pool.actorCount == 0)
        return;
    for (uint_t i = 0; i < Pool.actorCount - 1; i++) {
        swapped = false;
        for (uint_t j = 0; j < Pool.actorCount - i - 1; j++)
            swap_actors(j, &swapped);
        if (swapped == false)
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
void draw(void)
{
    for (uint_t i = 0; i < Editor.bCount; i++)
        prop_draw(Editor.bProps[i]);
    sort_actors_pool();
    for (uint_t i = 0; i < Pool.actorCount; i++)
        actor_draw(Pool.actors[i]);
    for (uint_t i = 0; i < Editor.fCount; i++)
        prop_draw(Editor.fProps[i]);
    draw_bullets();
    draw_debug_safe();
}
