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
static void spinner(entity_t *evil)
{
    v2f_t direction;

    direction.x = rand() % 2 ? -5.0f : 5.0f;
    direction.y = rand() % 2 ? -5.0f : 5.0f;
    if (equal2f((v2f_t){fabs(evil->vector.x), fabs(evil->vector.y)},
        V2F(5.0f, 0.0f))){
        evil->vector = direction;
        evil->wanted_position = evil->actor->position;
    }
    spinning_movement(evil);
    collision_hit(evil);
    if (evil->bounce >= 7){
        evil->bounce = 0;
        evil->status = Dazed;
        evil->last_action = Time.currentTime;
        evil->can_attack = !evil->can_attack;
        actor_set_sheet(evil->actor, "default");
        return;
    }
    evil->actor->invincible = true;
    actor_set_anim(evil->actor, "spin");
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
void multishot_calc(entity_t *evil, int angle)
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
void firing(entity_t *evil, uint_t ball_amount, int offset)
{
    uint_t pair_tax = offset / 2;

    if ((ball_amount % 2)) {
        create_bullet(evil->actor, Player.ref->position, evil->weapon);
        pair_tax = 0;
    }
    for (uint_t i = 1; i < ((ball_amount / 2) + 1); i++)
        multishot_calc(evil, (i == 1 && pair_tax) ? i * pair_tax :
            (i * offset) - pair_tax);
}

///////////////////////////////////////////////////////////////////////////////
static void shooting(entity_t *evil)
{
    ulong_t elsp = (Time.currentTime - evil->last_action);

    if (elsp < evil->firerate && !(evil->actor->self ==
        Assets.creatures[CREATURE_ELITE_FOX] && evil->attack_amount < 5 &&
        elsp > 125))
        return;
    if (evil->actor->self == Assets.creatures[CREATURE_ELITE_FOX]) {
        evil->attack_amount++;
        if (evil->attack_amount == 6)
            evil->attack_amount = 1;
    }
    firing(evil, evil->ball_count, 10);
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
    if (evil->attack_types == Spinjutsu)
        spinner(evil);
    if (distance2f(evil->actor->position, Player.ref->position) >
        evil->attack_radius)
        return;
    if (evil->attack_types == Shooter || evil->attack_types == Sniper)
        shooting(evil);
    return;
}
