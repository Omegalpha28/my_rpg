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
static void multishot(entity_t *evil, int angle)
{
    v2f_t bullet_position;
    float distance = 100.0;
    float dx = Player.ref->position.x - evil->actor->position.x;
    float dy = Player.ref->position.y - evil->actor->position.y;
    float base_angle = atan2(dy, dx);

    bullet_position.x = evil->actor->position.x + cos(base_angle +
        DEG2RAD(angle)) * distance;
    bullet_position.y = evil->actor->position.y + sin(base_angle +
        DEG2RAD(angle)) * distance;
    create_bullet(evil->actor, bullet_position, evil->weapon);
    bullet_position.x = evil->actor->position.x + cos(base_angle -
        DEG2RAD(angle)) * distance;
    bullet_position.y = evil->actor->position.y + sin(base_angle -
        DEG2RAD(angle)) * distance;
    create_bullet(evil->actor, bullet_position, evil->weapon);
}

///////////////////////////////////////////////////////////////////////////////
static void shooting(entity_t *evil)
{
    uint_t pair_tax = 5;

    if ((Time.currentTime - evil->last_action) < evil->firerate)
        return;
    if ((evil->ball_count % 2)) {
        create_bullet(evil->actor, Player.ref->position, evil->weapon);
        pair_tax = 0;
    }
    for (uint_t i = 1; i < ((evil->ball_count / 2) + 1); i++){
        if (i == 1 && pair_tax)
            multishot(evil, i * (10 - pair_tax));
        else
            multishot(evil, (i * (10 - pair_tax)) + pair_tax);
    }
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
    if (distance2f(evil->actor->position, Player.ref->position) >
        evil->attack_radius)
        return;
    if (evil->attack_types == Shooter || evil->attack_types == Sniper)
        shooting(evil);
    return;
}
