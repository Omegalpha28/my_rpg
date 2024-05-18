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

///////////////////////////////////////////////////////////////////////////////
void use_competence(void)
{
    return;
}

///////////////////////////////////////////////////////////////////////////////
void player_movement(void)
{
    Player.velocity = (v2f_t){0.0f, 0.0f};
    if (UP && !DANCE && !DASH)
        Player.velocity.y += -SPEED;
    if (DOWN && !DANCE && !DASH)
        Player.velocity.y += SPEED;
    if (LEFT && !DANCE && !DASH)
        Player.velocity.x += -SPEED;
    if (RIGHT && !DANCE && !DASH)
        Player.velocity.x += SPEED;
    get_last_input();
    Player.velocity = multiply2f(normalize2f(Player.velocity),
        V2F1(Time.deltaTime / 15));
    if (!DASH && !DANCE)
        actor_set_anim(Player.ref, (Player.velocity.x != 0.0f ||
            Player.velocity.y != 0.0f) ? "walk" : "idle");
    if (DANCE)
        actor_set_anim(Player.ref, "dance");
    dash_movement();
}

///////////////////////////////////////////////////////////////////////////////
static void dash_animation(void)
{
    v2f_t velocity = Player.last_velocity;

    actor_set_anim(Player.ref, "dash");
    if (!Player.ref->done) {
        if ((UP && velocity.y < 0.0f) || velocity.y < 0.0f)
            Player.velocity.y += -SPEED;
        if ((DOWN && velocity.y > 0.0f) || velocity.y > 0.0f)
            Player.velocity.y += SPEED;
        if ((LEFT && velocity.x < 0.0f) || velocity.x < 0.0f)
            Player.velocity.x += -SPEED;
        if ((RIGHT && velocity.x > 0.0f) || velocity.x > 0.0f)
            Player.velocity.x += SPEED;
        Player.velocity = multiply2f(normalize2f(Player.velocity),
            V2F1(Time.deltaTime / (10 + (8 * (clamp(Player.ref->frame - 26, 0,
                99))))));
        actor_move(Player.ref, Player.velocity);
        Player.ref->scale.x = Player.velocity.x < 0.0f ? -1.0f : 1.0f;
        camera_move();
    }
}

///////////////////////////////////////////////////////////////////////////////
void dash_movement(void)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    Player.ref->scale.x = Player.ref->position.x > cr.x ? -1.0f : 1.0f;
    if (DASH && !DANCE) {
        if (!CMP(Player.ref->self->sheets[Player.ref->sheetId]->
            anims[Player.ref->animId]->name, "dash"))
            sfx(SFX_PLAYER_DASH);
        dash_animation();
    }
    if (Player.ref->done && !DANCE && DASH) {
        actor_set_anim(Player.ref, (Player.velocity.x != 0.0f ||
            Player.velocity.y != 0.0f) ? "walk" : "idle");
        DASH = false;
    }
    actor_move(Player.ref, multiply2f(Player.velocity, V2F1(Player.speed)));
    camera_move();
}
