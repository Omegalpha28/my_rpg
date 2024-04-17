/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** shooters
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void shooter_ai(entity_t *evil)
{
    v2f_t move = movetowards2f(evil->actor->position,
        endpoint2f(Player.ref->position, evil->actor->position, evil->radius),
        (evil->speed * Time.deltaTime) / 25);
    v2f_t velocity = subtract2f(move, evil->actor->position);

    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    evil->actor->position = move;
    actor_set_anim(evil->actor, velocity.x != 0.0f || velocity.y != 0.0f ?
        "walk" : "idle");
    actor_draw(evil->actor);
}

