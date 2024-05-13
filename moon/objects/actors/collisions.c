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
static sfBool intersect(sfIntRect actor, sfIntRect prop)
{
    prop.top -= (prop.height / 2.0f);
    actor.top -= (actor.height / 2.0f);
    prop.height -= (actor.height / 2.0f);
    prop.left -= (prop.width / 2.0f);
    actor.left -= (actor.width / 2.0f);
    return (sfIntRect_intersects(&actor, &prop, NULL));
}

///////////////////////////////////////////////////////////////////////////////
static void collision_blocker(recti_t actor, recti_t prop, int index)
{
    if (intersect((recti_t){actor.left, Pool.actors[index]->old_pos.y,
        actor.width, actor.height}, prop))
        Pool.actors[index]->position.x = Pool.actors[index]->old_pos.x;
    if (intersect((recti_t){Pool.actors[index]->old_pos.x, actor.top,
        actor.width, actor.height}, prop))
        Pool.actors[index]->position.y = Pool.actors[index]->old_pos.y;
}

///////////////////////////////////////////////////////////////////////////////
static void collisions_check(int index)
{
    recti_t actor = (Pool.actors[index]->self->
        sheets[Pool.actors[index]->sheetId]->image->mask);
    recti_t prop;

    actor.left = (int)Pool.actors[index]->position.x;
    actor.top = (int)Pool.actors[index]->position.y;
    for (size_t i = 0; i < Pool.propCount; i++) {
        if (!Pool.props[i]->collision || (DASH && Pool.actors[index] ==
            Player.ref && CMP(Pool.props[i]->self->name, "water")))
            continue;
        prop = Pool.props[i]->self->image->mask;
        prop.left = (int)Pool.props[i]->position.x;
        prop.top = (int)Pool.props[i]->position.y;
        collision_blocker(actor, prop, index);
    }
    Pool.actors[index]->old_pos = Pool.actors[index]->position;
}

///////////////////////////////////////////////////////////////////////////////
void update_collisions(void)
{
    for (size_t i = 0; i < Pool.actorCount; i++)
        collisions_check(i);
}
