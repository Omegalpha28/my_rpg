/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** collisions
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief in case of collisions, blocks the enemy in its position, not
/// allowing it to go through it.
///
/// \param evil         Pointer to the enemy info structure.
/// \param prop_pos     position of current prop in collision.
/// \param prop_width
/// \param prop_height
///
///////////////////////////////////////////////////////////////////////////////
static void collision_blocker(entity_t *evil, v2f_t prop_pos, int prop_width,
    int prop_height)
{
    float overlapX = prop_width - fabs(evil->actor->position.x - prop_pos.x);
    float overlapY = prop_height - fabs(evil->actor->position.y +
        evil->collision - prop_pos.y);

    if (overlapX < overlapY)
        evil->actor->position.x += (overlapX *
            ((evil->actor->position.x - prop_pos.x > 0) ? 1 : -1));
    else {
        if (evil->actor->position.y - prop_pos.y > 0)
            evil->actor->position.y += (overlapY + evil->collision);
        else
            evil->actor->position.y -= (overlapY);
    }
}

///////////////////////////////////////////////////////////////////////////////
void collision_check(entity_t *evil)
{
    v2f_t evil_pos = evil->actor->position;
    v2f_t prop_pos;
    int prop_width;
    int prop_height;

    for (size_t i = 0; i < Editor.bCount; i++) {
        if (!Editor.bProps[i]->collision)
            continue;
        prop_pos = Editor.bProps[i]->position;
        prop_width = Editor.bProps[i]->self->image->mask.width / 2;
        prop_height = Editor.bProps[i]->self->image->mask.height / 2;
        if (evil_pos.x <= (prop_pos.x + prop_width) &&
            evil_pos.x >= (prop_pos.x - prop_width) &&
            evil_pos.y <= (prop_pos.y + prop_height) &&
            evil_pos.y + evil->collision >= (prop_pos.y - prop_height)) {
                collision_blocker(evil, prop_pos, prop_width, prop_height);
        }
    }
}
