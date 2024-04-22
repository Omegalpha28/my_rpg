/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** action
*/


///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

void dashing(entity_t *evil)
{
    v2f_t move;
    v2f_t velocity;

    if (equal2f(evil->wanted_position, evil->actor->position)){
        if (!evil->attack_started){
            evil->wanted_position = endpoint2f(evil->actor->position,
                Player.ref->position, 150.0f);
            evil->attack_started = !evil->attack_started;
        } else {
            evil->can_attack = !evil->can_attack;
            evil->last_action = Time.currentTime;
        }
    }
    move = movetowards2f(evil->actor->position, evil->wanted_position,
        (evil->speed * 5 * Time.deltaTime) / 25);
    velocity = subtract2f(move, evil->actor->position);
    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    evil->actor->position = move;
    evil->invincible = true;
    actor_set_anim(evil->actor, velocity.x != 0.0f || velocity.y != 0.0f ?
        "angrywalk" : "walk");
}

///////////////////////////////////////////////////////////////////////////////
void enemy_action(entity_t *evil)
{
    if (!evil->can_attack &&
        (Time.currentTime - evil->last_action) >= evil->cooldown){
        evil->can_attack = !evil->can_attack;
        evil->wanted_position = evil->actor->position;
        evil->attack_started = false;
    }
    if (!evil->can_attack)
        return;
    if (evil->attack_types == Dash)
        dashing(evil);
    return;
}
