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

    if (evt.button == Keys.shoot && pressed)
        bullet_creation(0);
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
    if (evt.code == Keys.dash.code)
        Keys.dash.pressed = pressed;
    if (evt.code == Keys.dance.code && !pressed) {
        Keys.dance.pressed = released && !DANCE ? true : false;
    }
}

///////////////////////////////////////////////////////////////////////////////
void parse_key_input(sfKeyEvent evt)
{
    bool_t pressed = (evt.type == sfEvtKeyPressed);
    bool_t released = (evt.type == sfEvtKeyReleased);

    parse_movement_key_input(evt, pressed, released);
}
