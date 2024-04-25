/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** input
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void parse_mouse_input(sfMouseButtonEvent evt)
{
    bool_t pressed = (evt.type == sfEvtMouseButtonPressed);

    if (evt.button == Keys.shoot && pressed && !DANCE && !DASH)
        bullet_creation(0, 26, 5, 130);
}

void get_last_input(void)
{
    v2f_t vel = Player.last_velocity;

    if ((UP || DOWN) && !RIGHT && !LEFT && !DASH)
        vel.x = 0.0f;
    if ((RIGHT || LEFT) && !UP && !DOWN && !DASH)
        vel.y = 0.0f;
    vel.x = Player.velocity.x != 0.0f ? Player.velocity.x : vel.x;
    vel.y = Player.velocity.y != 0.0f ? Player.velocity.y : vel.y;
    Player.last_velocity = vel;
}

///////////////////////////////////////////////////////////////////////////////
static void parse_movement_key_input(sfKeyEvent evt, bool_t pressed,
    bool_t released)
{
    if (evt.code == Keys.up.code || evt.code == ALT_UP)
        Keys.up.pressed = pressed;
    if (evt.code == Keys.down.code || evt.code == ALT_DOWN)
        Keys.down.pressed = pressed;
    if (evt.code == Keys.right.code || evt.code == ALT_RIGHT)
        Keys.right.pressed = pressed;
    if (evt.code == Keys.left.code || evt.code == ALT_LEFT)
        Keys.left.pressed = pressed;
    if (evt.code == Keys.dash.code && pressed)
        Keys.dash.pressed = pressed;
    if (evt.code == Keys.heal.code)
        use_competence();
    if (evt.code == Keys.dance.code && !pressed) {
        Keys.dance.pressed = released && !DANCE ? true : false;
        if (DANCE) {
            sfMusic_play(find_music("blingblangblang"));
            sfMusic_setLoop(find_music("blingblangblang"), sfTrue);
        } else
            sfMusic_pause(find_music("blingblangblang"));
    }
}

///////////////////////////////////////////////////////////////////////////////
void parse_key_input(sfKeyEvent evt)
{
    bool_t pressed = (evt.type == sfEvtKeyPressed);
    bool_t released = (evt.type == sfEvtKeyReleased);

    parse_movement_key_input(evt, pressed, released);
}
