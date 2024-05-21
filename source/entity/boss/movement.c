/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** movement
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

static void idle(entity_t *boss)
{
    v2f_t move;
    v2f_t velocity;

    move = movetowards2f(boss->actor->position, boss->wanted_position,
        (boss->speed * Time.deltaTime) / 25);
    velocity = subtract2f(move, boss->actor->position);
    boss->actor->position = move;
    actor_set_anim(boss->actor, velocity.x != 0.0f || velocity.y != 0.0f ?
        "walk" : "idle");
}

///////////////////////////////////////////////////////////////////////////////
void crab_movement(entity_t *boss)
{
    idle(boss);
    return;
}

/*
redirection to top right. after spin dash.

move left and right

same y axis going to

*/

///////////////////////////////////////////////////////////////////////////////
void cthulu_movement(entity_t *boss)
{
    boss = boss;
    return;
}

///////////////////////////////////////////////////////////////////////////////
void boss_movement(entity_t *boss)
{
    if (boss->actor->self->id == CREATURE_CRAB_BOSS)
        crab_movement(boss);
    if (boss->actor->self->id == CTHULU_TODO)
        cthulu_movement(boss);
    return;
}
