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
    if (DASH && Player.ref == actor)
        return;
    actor->health -= (Player.ref == actor) ? 1 : 15;
    actor->damaged = true;
}

///////////////////////////////////////////////////////////////////////////////
bool_t collision_hit(recti_t attack_mask, recti_t recipient_mask, v2f_t
    attack_pos, v2f_t recipient_pos)
{
    attack_mask.left = attack_pos.x - (attack_mask.width / 2.0f);
    attack_mask.top = attack_pos.y - (attack_mask.height / 2.0f);
    recipient_mask.left = recipient_pos.x - (recipient_mask.width / 2.0f);
    recipient_mask.top = recipient_pos.y - (recipient_mask.height / 2.0f);
    if (sfIntRect_intersects(&attack_mask, &recipient_mask, NULL))
        return true;
    return false;
}

///////////////////////////////////////////////////////////////////////////////
void dash_collision_hit(entity_t *evil)
{
    if (!collision_hit(
    evil->actor->self->sheets[evil->actor->sheetId]->image->mask,
    Player.ref->self->sheets[Player.ref->sheetId]->image->mask,
    evil->actor->position, Player.ref->position))
        evil->is_attack = false;
    else
        if (!evil->is_attack){
            collision_damage(Player.ref);
            evil->is_attack = true;
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
    crab->last_action = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
void spinning_movement(entity_t *evil)
{
    actor_set_sheet(evil->actor, evil->curr_phase == 0 ? "spin" : "rage_spin");
    actor_set_anim(evil->actor, "spin");
    if (equal2f(V2F(floorf(evil->wanted_position.x),
        floorf(evil->wanted_position.y)), V2F(floorf(evil->actor->position.x),
        floorf(evil->actor->position.y))))
        get_wanted_position(evil);
    evil->actor->position = movetowards2f(evil->actor->position,
        evil->wanted_position, (evil->speed * Time.deltaTime) / 2);
}
