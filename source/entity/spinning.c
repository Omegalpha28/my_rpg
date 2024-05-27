/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** spinning
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
static void collision_damage(actor_t *actor)
{
    if (actor->invincible)
        return;
    actor->health -= (Player.ref == actor) ? 1 : 15;
}

///////////////////////////////////////////////////////////////////////////////
void collision_hit(entity_t *evil)
{
    recti_t arect = evil->actor->self->
        sheets[evil->actor->sheetId]->image->mask;
    recti_t prect = Player.ref->self->sheets[Player.ref->sheetId]->image->mask;

    arect.left = evil->actor->position.x - (arect.width / 2.0f);
    arect.top = evil->actor->position.y - (arect.height / 2.0f);
    prect.left = Player.ref->position.x - (prect.width / 2.0f);
    prect.top = Player.ref->position.y - (prect.height / 2.0f);
    if (!sfIntRect_intersects(&arect, &prect, NULL))
        evil->attack_started = false;
    if (sfIntRect_intersects(&arect, &prect, NULL) && !evil->attack_started){
        collision_damage(Player.ref);
        evil->attack_started = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
static bool_t intersect_with_prop(v2f_t simpos, entity_t *crab, prop_t **prop)
{
    recti_t pmask;
    recti_t prect;
    recti_t arect = (crab->actor->self->
        sheets[crab->actor->sheetId]->image->mask);

    arect.left = simpos.x - (arect.width / 2.0f);
    arect.top = simpos.y - (arect.height / 2.0f);
    for (uint_t i = 0; i < Pool.propCount; i++) {
        if (!Pool.props[i]->collision)
            continue;
        pmask = Pool.props[i]->self->image->mask;
        prect = (recti_t){Pool.props[i]->position.x - pmask.width / 2.0f,
            Pool.props[i]->position.y - pmask.height / 2.0f, pmask.width,
            pmask.height};
        if (sfIntRect_intersects(&arect, &prect, NULL)) {
            *prop = Pool.props[i];
            return (true);
        }
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
/// \return 0 horizontal 1 vertical.
///////////////////////////////////////////////////////////////////////////////
static bool_t get_prop_direction(prop_t *prop, v2f_t sim_pos)
{
    recti_t pmask = prop->self->image->mask;
    recti_t pr = {prop->position.x - pmask.width / 2.0f, prop->position.y -
        pmask.height / 2.0f, pmask.width, pmask.height};
    float dx = sim_pos.x - (pr.left + pr.width / 2.0f);
    float dy = sim_pos.y - (pr.top + pr.height / 2.0f);

    return (fabs(dx) > fabs(dy) ? false : true);
}

///////////////////////////////////////////////////////////////////////////////
void get_wanted_position(entity_t *crab)
{
    v2f_t sim_position = crab->actor->position;
    prop_t *prop = NULL;

    while (!intersect_with_prop(sim_position, crab, &prop))
        sim_position = add2f(sim_position, crab->vector);
    crab->wanted_position = subtract2f(sim_position, crab->vector);
    if (get_prop_direction(prop, sim_position))
        crab->vector.y *= -1;
    else
        crab->vector.x *= -1;
    crab->bounce++;
}

///////////////////////////////////////////////////////////////////////////////
void spinning_movement(entity_t *evil)
{
    if (equal2f(V2F(floorf(evil->wanted_position.x),
        floorf(evil->wanted_position.y)), V2F(floorf(evil->actor->position.x),
        floorf(evil->actor->position.y))))
        get_wanted_position(evil);
    evil->actor->position = movetowards2f(evil->actor->position,
        evil->wanted_position, (evil->speed * Time.deltaTime) / 2);
}
