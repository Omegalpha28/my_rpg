/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** animation
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

void player_movement(void)
{
    actor_t *act = Player.ref;
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    Player.velocity = (v2f_t){0.0f, 0.0f};
    if (UP)
        Player.velocity.y += -SPEED;
    if (DOWN)
        Player.velocity.y += SPEED;
    if (LEFT)
        Player.velocity.x += -SPEED;
    if (RIGHT)
        Player.velocity.x += SPEED;
    Player.velocity = normalize2f(Player.velocity);
    Player.velocity.x *= Time.deltaTime / 15;
    Player.velocity.y *= Time.deltaTime / 15;
    actor_set_anim(act, (Player.velocity.x != 0.0f ||
        Player.velocity.y != 0.0f) ? "walk" : "idle");
    actor_move(act, Player.velocity);
    act->scale.x = act->position.x > cr.x ? -1.0f : 1.0f;
}

void dash_movement(void)
{
    actor_t *act = Player.ref;
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    if (UP && DASH)
        Player.velocity.y += -SPEED * 10;
    if (DOWN && DASH)
        Player.velocity.y += SPEED * 10;
    if (LEFT && DASH)
        Player.velocity.x += -SPEED * 10;
    if (RIGHT && DASH)
        Player.velocity.x += SPEED * 10;
    Player.velocity = normalize2f(Player.velocity);
    Player.velocity.x *= Time.deltaTime / 15;
    Player.velocity.y *= Time.deltaTime / 15;
    actor_set_anim(act, "dash");
    actor_move(act, Player.velocity);
    act->scale.x = act->position.x > cr.x ? -1.0f : 1.0f;
}
