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
static void swap_entities(uint_t j, bool_t *swapped)
{
    entity_t *tmp = Entities.array[j];

    if (Entities.array[j]->actor->position.y >
        Entities.array[j + 1]->actor->position.y)
        return;
    Entities.array[j] = Entities.array[j + 1];
    Entities.array[j + 1] = tmp;
    *swapped = true;
}

///////////////////////////////////////////////////////////////////////////////
void sort_entities_verticaly(void)
{
    bool_t swapped = false;

    if (Entities.count == 0)
        return;
    for (uint_t i = 0; i < Entities.count - 1; i++) {
        swapped = false;
        for (uint_t j = 0; j < Entities.count - i - 1; j++)
            swap_entities(j, &swapped);
        if (swapped == false)
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
void draw(void)
{
    bool_t playerDrawn = false;

    for (uint_t i = 0; i < Editor.bCount; i++)
        prop_draw(Editor.bProps[i]);
    sort_entities_verticaly();
    for (uint_t i = 0; i < Entities.count; i++) {
        if (!playerDrawn && Entities.array[i]->actor->position.y >
            Player.ref->position.y) {
            actor_draw(Player.ref);
            playerDrawn = true;
        }
        actor_draw(Entities.array[i]->actor);
    }
    if (!playerDrawn)
        actor_draw(Player.ref);
    for (uint_t i = 0; i < Editor.fCount; i++)
        prop_draw(Editor.fProps[i]);
    draw_bullets();
    draw_debug_safe();
}
