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
    if (evt.button != Keys.shoot)
        return;
}

///////////////////////////////////////////////////////////////////////////////
static void parse_movement_key_input(sfKeyEvent evt, bool_t pressed)
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
        dash_movement();
}

///////////////////////////////////////////////////////////////////////////////
void parse_key_input(sfKeyEvent evt)
{
    bool_t pressed = (evt.type == sfEvtKeyPressed);

    parse_movement_key_input(evt, pressed);
}
