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

/*
top stat:

y: 145 or 160:

x :
*/

///////////////////////////////////////////////////////////////////////////////
static recti_t get_actor_box(entity_t *evil)
{
    recti_t actor = (evil->actor->self->
        sheets[evil->actor->sheetId]->image->mask);

    actor.left = evil->actor->position.x;
    actor.top  = evil->actor->position.y;
    actor.top -= (actor.height / 2.0f);
    actor.left -= (actor.width / 2.0f);
    return (actor);
}

///////////////////////////////////////////////////////////////////////////////
static float get_collision_angle(recti_t pr, entity_t *evil)
{
    float dx = evil->actor->position.x - (pr.left + pr.width / 2.0f);
    float dy = evil->actor->position.y - (pr.top + pr.height / 2.0f);

    if (fabs(dx) > fabs(dy)) {
        if (dx > 0)
            return (180.0f);
        return (0.0f);
    } else {
        if (dy > 0)
            return (-90.0f);
        return (90.0f);
    }
}


///////////////////////////////////////////////////////////////////////////////
static void wall_collision(entity_t *evil, prop_t *prop, v2f_t velocity)
{
    recti_t pmask = prop->self->image->mask;
    recti_t prect = {prop->position.x - pmask.width / 2.0f, prop->position.y - pmask.height / 2.0f, pmask.width, pmask.height};
    recti_t arect = get_actor_box(evil);
    float angle = get_collision_angle(prect, evil);
    v2f_t prop_velocity = subtract2f(evil->actor->position, prop->position);


    if (!sfIntRect_intersects(&arect, &prect, NULL))
        return;
    if (angle == 180.0f){
        if ((velocity.x > 0 && prop_velocity.x > 0) || (velocity.x < 0 && prop_velocity.x < 0))
            evil->wanted_position.x = -evil->wanted_position.x;
    } else if (fabs(angle) == 90.0f){
        if ((velocity.y > 0 && prop_velocity.y > 0) || (velocity.y < 0 && prop_velocity.y < 0))
            evil->wanted_position.y = -evil->wanted_position.y;
    }
}


///////////////////////////////////////////////////////////////////////////////
static void bounce_check(entity_t *evil, v2f_t velocity)
{
    for (uint_t i = 0; i < Pool.propCount; i++) {
        if (!Pool.props[i]->collision)
            continue;
        wall_collision(evil, Pool.props[i], velocity);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void idle(entity_t *boss)
{
    v2f_t move;
    v2f_t velocity;

    move = movetowards2f(boss->actor->position, boss->wanted_position,
        (boss->speed * Time.deltaTime) / 25);
    velocity = subtract2f(move, boss->actor->position);
    boss->wanted_position = (v2f_t){boss->actor->position.x + 200.0f, boss->actor->position.y};
    bounce_check(boss, velocity);

    boss->actor->position = move;
    actor_set_sheet(boss->actor, velocity.x != 0.0f || velocity.y != 0.0f ?
        "walk" : "idle");
}

///////////////////////////////////////////////////////////////////////////////
void crab_movement(entity_t *boss)
{
    idle(boss);
    return;
}

/*

at the top check.

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
