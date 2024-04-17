/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** melee
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void melee(entity_t *evil)
{
    v2f_t move = movetowards2f(evil->actor->position,
        endpoint2f(Player.ref->position, evil->actor->position, evil->radius),
        (evil->speed * Time.deltaTime) / 25);
    v2f_t velocity = subtract2f(move, evil->actor->position);
    float_t curr_rad = distance2f(evil->actor->position, Player.ref->position);

    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    if (curr_rad >= evil->radius){
        evil->actor->position = move;
    } else {
        evil->actor->scale.x *= -1;
        velocity = (v2f_t){0.0f, 0.0f};
    }
    actor_set_anim(evil->actor, velocity.x != 0.0f || velocity.y != 0.0f ?
        "walk" : "idle");
    actor_draw(evil->actor);
}
