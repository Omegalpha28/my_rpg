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
static void patrol_position_calc(entity_t *evil)
{
    if (equal2f(evil->wanted_position, evil->actor->position) ||
        Time.currentTime - evil->movement >= 3000){
        if (!evil->attack_started){
            evil->attack_started = !evil->attack_started;
            evil->last_action = Time.currentTime;
            evil->movement = Time.currentTime;
        }
        if (Time.currentTime - evil->last_action >=
            (ulong_t)(rand() % 500 + 500) && evil->attack_started){
            evil->wanted_position = rand_pos(evil->actor->position, 30, 50);
            evil->attack_started = !evil->attack_started;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for Patrolling behavioral movement.
///
/// generates a new position to idly walk to while checking its surroundings.
///
/// \param evil         Entity in patrol mode.
///
///////////////////////////////////////////////////////////////////////////////
static void patrolling(entity_t *evil)
{
    v2f_t move;
    v2f_t velocity;

    if (dist2f(evil->actor->position, Player.ref->position) <= evil->insight
        && evil->attack_types != Bomber) {
        evil->status = evil->attack_types == Sniper ? ranger : Agressive;
        return;
    }
    if (evil->attack_types == Bomber && (Time.currentTime - evil->cooldown) >=
        5000)
        evil->can_attack = true;
    patrol_position_calc(evil);
    move = movetowards2f(evil->actor->position, evil->wanted_position,
        (evil->speed * Time.deltaTime) / 25);
    velocity = subtract2f(move, evil->actor->position);
    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    evil->actor->position = move;
    actor_set_anim(evil->actor, velocity.x != 0.0f || velocity.y != 0.0f ?
        "walk" : "idle");
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for aggressive behavioral movement.
///
/// is now in chase/attack mode. the Entities movement goal is to stay with in
/// a certain attack radius of the Player.
///
/// \param evil         Entity is approaching.
///
///////////////////////////////////////////////////////////////////////////////
static void approaching(entity_t *evil)
{
    v2f_t move = movetowards2f(evil->actor->position,
        endpoint2f(Player.ref->position, evil->actor->position,
            evil->attack_radius), (evil->speed * Time.deltaTime) / 25);
    float_t curr_rad = distance2f(evil->actor->position, Player.ref->position);

    if (dist2f(evil->actor->position, Player.ref->position) >
        evil->insight * 2){
        evil->status = Patrol;
        evil->wanted_position = evil->actor->position;
        return;
    }
    evil->actor->scale.x = evil->actor->position.x - Player.ref->position.x > 0
        ? -1.0f : 1.0f;
    if ((int)curr_rad >= (int)evil->attack_radius || evil->status == ranger)
        evil->actor->position = move;
    actor_set_anim(evil->actor, !equal2f(evil->actor->position,
        evil->wanted_position) ? "walk" : "idle");
    evil->wanted_position = evil->actor->position;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for stun affect.
///
/// when a entity is stun, they no longer move untill the status effect is
/// over. once recovered they will return to idle mode.
///
/// \param evil         Entity is in a daz.
///
///////////////////////////////////////////////////////////////////////////////
static void stunned(entity_t *evil)
{
    actor_set_anim(evil->actor, "tired");
    if (Time.currentTime - evil->last_action < evil->dizzy)
        return;
    evil->status = Patrol;
    evil->last_action = Time.currentTime;
    evil->movement = Time.currentTime;
    return;
}

///////////////////////////////////////////////////////////////////////////////
static void no_movement(entity_t *evil)
{
    if (Time.currentTime - evil->last_action >= evil->dizzy * 1.3)
        evil->can_attack = true;
    actor_set_anim(evil->actor, "idle");
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for evasion of the Entity.
///
/// In this case, they flee in one x axis direction for a certain amount of
/// time and then return back to patrol mode
///
/// \param evil         Entity running away.
///
///////////////////////////////////////////////////////////////////////////////
static void fleeing(entity_t *evil)
{
    v2f_t move;

    if (Time.currentTime - evil->last_action >= evil->dizzy){
        evil->status = Patrol;
        evil->last_action = Time.currentTime;
        evil->movement = Time.currentTime;
        evil->cooldown = Time.currentTime;
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
    if ((evil->attack_types == Dash || evil->attack_types == Spinjutsu)
        && evil->can_attack)
        return;
    evil->actor->invincible = false;
    if (evil->attack_types == Spinjutsu && evil->status == Patrol)
        no_movement(evil);
    if (evil->status == Patrol && evil->attack_types != Spinjutsu)
        patrolling(evil);
    if (evil->status == Agressive || evil->status == ranger)
        approaching(evil);
    if (evil->status == Dazed)
        stunned(evil);
    if (evil->status == Fear)
        fleeing(evil);
}
