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

    if (evt.button == Setting.shoot && pressed && !DANCE && !DASH)
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
    if (evt.code == Setting.up.code || evt.code == ALT_UP)
        UP = pressed;
    if (evt.code == Setting.down.code || evt.code == ALT_DOWN)
        DOWN = pressed;
    if (evt.code == Setting.right.code || evt.code == ALT_RIGHT)
        RIGHT = pressed;
    if (evt.code == Setting.left.code || evt.code == ALT_LEFT)
        LEFT = pressed;
    if (evt.code == Setting.dash.code && pressed)
        DASH = pressed;
    if (evt.code == Setting.heal.code)
        use_competence();
    if (evt.code == Setting.dance.code && !pressed) {
        DANCE = released && !DANCE ? true : false;
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
