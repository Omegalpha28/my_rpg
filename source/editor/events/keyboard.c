/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** keyboard
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_prop_movement(sfKeyEvent evt)
{
    if (Editor.focus && (evt.code == ALT_UP || evt.code == ALT_DOWN))
        Editor.focus->position.y += evt.code == sfKeyUp ? -1 : +1;
    if (Editor.focus && (evt.code == sfKeyLeft || evt.code == sfKeyRight))
        Editor.focus->position.x += evt.code == sfKeyLeft ? -1 : +1;
    if (Editor.focus && (evt.code >= sfKeyLeft && evt.code <= sfKeyDown))
        prop_set_transform(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_copy_paste(sfKeyEvent evt)
{
    bool_t ctrl = PRESSED(sfKeyLControl) || PRESSED(sfKeyRControl);

    if (Editor.focus && (evt.code == sfKeyC && ctrl))
        Editor.copy = Editor.focus;
    if (Editor.copy && (evt.code == sfKeyV && ctrl)) {
        add_prop(Editor.copy->self, &(Editor.fProps), &(Editor.fCount));
        Editor.fProps[Editor.fCount - 1]->position.x =
            floorf(Editor.crtMouse.x);
        Editor.fProps[Editor.fCount - 1]->position.y =
            floorf(Editor.crtMouse.y);
        prop_set_transform(Editor.fProps[Editor.fCount - 1]);
        Editor.focus = Editor.fProps[Editor.fCount - 1];
    }
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_pressed(sfKeyEvent evt)
{
    handle_editor_key_prop_movement(evt);
    handle_editor_key_copy_paste(evt);
}
