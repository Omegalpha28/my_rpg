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
/// \param act_hitbox       Hitbox of current actor.
/// \param act_pos          Position f current actor.
/// \param prop_pos         Position of current prop in collision.
/// \param prop_dimension   Vector consisting of x and y dimensions of prop.
///
///////////////////////////////////////////////////////////////////////////////
static v2f_t collision_blocker(float act_hitbox, v2f_t act_pos, v2f_t prop_pos,
    v2i_t prop_dimension)
{
    float overlapX = prop_dimension.x - fabs(act_pos.x - prop_pos.x);
    float overlapY = prop_dimension.y - fabs(act_pos.y +
        act_hitbox - prop_pos.y);

    if (overlapX < overlapY)
        act_pos.x += (overlapX * ((act_pos.x - prop_pos.x > 0) ? 1 : -1));
    else {
        if (act_pos.y - prop_pos.y > 0)
            act_pos.y += (overlapY + act_hitbox);
        else
            act_pos.y -= (overlapY);
    }
    return act_pos;
}

///////////////////////////////////////////////////////////////////////////////
void collision_check(int index)
{
    v2f_t act_pos = Pool.actors[index]->position;
    v2f_t prop_pos;
    v2i_t prop_dimension;
    float act_hitbox = (float)(Pool.actors[index]->self->sheets[Pool.actors
        [index]->sheetId]->image->mask.height) / 2;

    for (size_t i = 0; i < Pool.propCount; i++) {
        if (!Pool.props[i]->collision)
            continue;
        prop_pos = Pool.props[i]->position;
        prop_dimension.x = Pool.props[i]->self->image->mask.width / 2;
        prop_dimension.y = Pool.props[i]->self->image->mask.height / 2;
        if (act_pos.x <= (prop_pos.x + prop_dimension.x) &&
            act_pos.x >= (prop_pos.x - prop_dimension.x) &&
            act_pos.y <= (prop_pos.y + prop_dimension.y) &&
            act_pos.y + act_hitbox >= (prop_pos.y - prop_dimension.y))
                Pool.actors[index]->position = collision_blocker(act_hitbox,
                    act_pos, prop_pos, prop_dimension);
    }
}

///////////////////////////////////////////////////////////////////////////////
void update_collisions(void)
{
    for (size_t i = 0; i < Pool.actorCount; i++){
        collision_check(i);
    }
}
