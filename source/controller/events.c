/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** events
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void parse_events(sfEvent evt)
{
    if (evt.type == sfEvtClosed)
        sfRenderWindow_close(Win.self);
    if (evt.type == sfEvtKeyPressed || evt.type == sfEvtKeyReleased)
        parse_key_input(evt.key);
    if (evt.type == sfEvtMouseButtonPressed ||
        evt.type == sfEvtMouseButtonReleased)
        parse_mouse_input(evt.mouseButton);
    if (evt.type == sfEvtKeyPressed && evt.key.code == sfKeyNumpad1)
        Player.weapon--;
    if (evt.type == sfEvtKeyPressed && evt.key.code == sfKeyNumpad2)
        Player.weapon++;
}
