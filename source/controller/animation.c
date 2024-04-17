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
    if (!DASH)
        actor_set_anim(act, (Player.velocity.x != 0.0f ||
            Player.velocity.y != 0.0f) ? "walk" : "idle");
    dash_movement();
}

void dash_movement(void)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    if (DASH) {
        Player.velocity = (v2f_t){0.0f, 0.0f};
        if (UP)
            Player.velocity.y += -SPEED * 5;
        if (DOWN)
            Player.velocity.y += SPEED * 5;
        if (LEFT)
            Player.velocity.x += -SPEED * 5;
        if (RIGHT)
            Player.velocity.x += SPEED * 5;
        Player.velocity = normalize2f(Player.velocity);
        Player.velocity.x *= Time.deltaTime / 15;
        Player.velocity.y *= Time.deltaTime / 15;
        actor_set_anim(Player.ref, "dash");
    }
    actor_move(Player.ref, Player.velocity);
    camera_move();
    Player.ref->scale.x = Player.ref->position.x > cr.x ? -1.0f : 1.0f;
}
