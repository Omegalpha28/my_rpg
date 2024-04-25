/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** events
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void handle_editor_events(sfEvent evt)
{
    if (evt.type == sfEvtClosed)
        sfRenderWindow_close(Win.self);
    if (evt.type == sfEvtMouseButtonPressed)
        handle_editor_mouse_button(evt.mouseButton);
    if (evt.type == sfEvtMouseButtonReleased)
        handle_editor_mouse_released(evt.mouseButton);
    if (evt.type == sfEvtMouseWheelScrolled)
        handle_editor_mouse_scroll(evt.mouseWheelScroll);
    if (evt.type == sfEvtKeyPressed)
        handle_editor_key_pressed(evt.key);
    if (evt.type == sfEvtMouseMoved)
        handle_mouse_move();
}
