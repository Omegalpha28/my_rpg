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

///////////////////////////////////////////////////////////////////////////////
bool_t v2f_empty(v2f_t vector)
{
    return (vector.x != 0.0f || vector.y != 0.0f);
}

///////////////////////////////////////////////////////////////////////////////
static void dashing(entity_t *evil)
{
    v2f_t move;

    if (equal2f(evil->wanted_position, evil->actor->position) ||
        (Time.currentTime - evil->movement) >= 4000){
        if (!evil->attack_started){
            evil->wanted_position = endpoint2f(evil->actor->position,
                Player.ref->position, 150.0f);
            evil->attack_started = !evil->attack_started;
            evil->movement = Time.currentTime;
        } else {
            evil->can_attack = !evil->can_attack;
            evil->last_action = Time.currentTime;
        }
    }
    move = movetowards2f(evil->actor->position, evil->wanted_position,
        (evil->speed * 5 * Time.deltaTime) / 25);
    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    evil->actor->position = move;
    evil->actor->invincible = true;
    actor_set_anim(evil->actor, "angrywalk");
}

///////////////////////////////////////////////////////////////////////////////
static void shooting(entity_t *evil)
{
    if ((Time.currentTime - evil->last_action) < evil->firerate)
        return;
    create_bullet(evil->actor, Player.ref->position, evil->weapon);
    evil->last_action = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
void enemy_action(entity_t *evil)
{
    if (!evil->can_attack && (Time.currentTime - evil->last_action) >=
        evil->cooldown){
        evil->can_attack = !evil->can_attack;
        evil->wanted_position = evil->actor->position;
        evil->attack_started = false;
    }
    if (!evil->can_attack)
        return;
    if (evil->attack_types == Dash)
        dashing(evil);
    if (evil->attack_types == Shooter || evil->attack_types == Sniper)
        shooting(evil);
    return;
}
