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


///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for Patrolling behavioral movement.
///
/// generates a new position to idly walk to while checking its surroundings.
///
/// \param evil         Entity in patrol mode.
///
///////////////////////////////////////////////////////////////////////////////
void patrolling(entity_t *evil)
{
    v2f_t move;

    if (dist2f(evil->actor->position, Player.ref->position) <= evil->insight
        && evil->attack != Bomber) {
        evil->status = Agressive;
        return;
    }
    if (equal2f(evil->wanted_position, evil->actor->position))
            evil->wanted_position = rand_pos(evil->actor->position, 30, 50);
    move = movetowards2f(evil->actor->position, evil->wanted_position,
        (evil->speed * Time.deltaTime) / 25);
    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    evil->actor->position = move;
    actor_set_anim(evil->actor, "walk");
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for aggressive behavioral movement.
///
/// is now in chase/attack mode. the Entities movement goal is to stay with in
/// a certain attack radius of the Player.
///
/// \param evil         Entity in patrol mode.
///
///////////////////////////////////////////////////////////////////////////////
void approaching(entity_t *evil)
{
    v2f_t move = movetowards2f(evil->actor->position,
        endpoint2f(Player.ref->position, evil->actor->position,
            evil->attack_radius), (evil->speed * Time.deltaTime) / 25);
    float_t curr_rad = distance2f(evil->actor->position, Player.ref->position);

    if (dist2f(evil->actor->position, Player.ref->position) >
        evil->insight * 2){
        evil->status = Patrol;
        return;
    }
    evil->actor->scale.x = evil->actor->position.x - Player.ref->position.x > 0
        ? -1.0f : 1.0f;
    if (curr_rad >= evil->attack_radius)
        evil->actor->position = move;
    actor_set_anim(evil->actor, equal2f(evil->actor->position, move) ?
        "walk" : "idle");
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for stun affect.
///
/// when a entity is stun, they no longer move untill the status effect is
/// over. once recovered they will return to idle mode.
///
/// \param evil         Entity in patrol mode.
///
///////////////////////////////////////////////////////////////////////////////
void stunned(entity_t *evil)
{
    if (evil->last_action - Time.currentTime >= evil->dizzy){
        evil->status = Patrol;
        evil->last_action = 0;
        return;
    }
    actor_set_anim(evil->actor, "tired");
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for evasion of the Entity.
///
/// In this case, they flee in one x axis direction for a certain amount of
/// time and then return back to patrol mode
///
/// \param evil         Entity in patrol mode.
///
///////////////////////////////////////////////////////////////////////////////
void fleeing(entity_t *evil)
{
    v2f_t move;

    if (evil->last_action - Time.currentTime >= evil->dizzy){
        evil->status = Patrol;
        evil->last_action = 0;
        return;
    }
    if (equal2f(evil->wanted_position, evil->actor->position))
            evil->wanted_position = flee_rand_pos(evil->actor->position,
                15, 25);
    move = movetowards2f(evil->actor->position, evil->wanted_position,
        (evil->speed * 1.5 * Time.deltaTime) / 25);
    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    evil->actor->position = move;
    actor_set_anim(evil->actor, "run");
}

///////////////////////////////////////////////////////////////////////////////
void enemy_movement(entity_t *evil)
{
    if (evil->status == Patrol)
        patrolling(evil);
    if (evil->status == Agressive)
        approaching(evil);
    if (evil->status == Dazed)
        stunned(evil);
    if (evil->status == Fear)
        fleeing(evil);
}
