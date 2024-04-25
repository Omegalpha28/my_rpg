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
    prop_t ***arr = Editor.layer == EDITOR_LAYER_FOREGROUND ?
        &(Editor.fProps) : &(Editor.bProps);
    uint_t *counter = Editor.layer == EDITOR_LAYER_FOREGROUND ?
        &(Editor.fCount) : &(Editor.bCount);

    if (Editor.focus && ((evt.code == sfKeyC || evt.code == sfKeyD) && ctrl))
        Editor.copy = Editor.focus->self;
    if ((Editor.copy && (evt.code == sfKeyV && ctrl)) || (Editor.focus &&
        (evt.code == sfKeyD && ctrl))) {
        add_prop(Editor.copy, arr, counter);
        (*arr)[(*counter) - 1]->position.x = floorf(Editor.crtMouse.x);
        (*arr)[(*counter) - 1]->position.y = floorf(Editor.crtMouse.y);
        prop_set_transform((*arr)[(*counter) - 1]);
        Editor.focus = (*arr)[(*counter) - 1];
    }
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_delete(sfKeyEvent evt)
{
    if (Editor.focus && (evt.code == sfKeyDelete || evt.code == sfKeyX)) {
        if (evt.code == sfKeyX)
            Editor.copy = Editor.focus->self;
        remove_prop(Editor.focus, &(Editor.fProps), &(Editor.fCount));
        remove_prop(Editor.focus, &(Editor.bProps), &(Editor.bCount));
        Editor.focus = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_animation(sfKeyEvent evt)
{
    if (Editor.focus && evt.code == sfKeySpace)
        prop_animate(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_canvas(sfKeyEvent evt)
{
    if (evt.code == sfKeyO) {
        Win.viewWidth = DEFAULT_VIEW_WIDTH;
        Win.viewHeight = (float)((float)(DEFAULT_VIEW_WIDTH /
            (float)Win.width)) * Win.height;
        sfView_setSize(Win.view, V2F(Win.viewWidth, Win.viewHeight));
        sfView_setCenter(Win.view, V2F1(0.0f));
        sfRenderWindow_setView(Win.self, Win.view);
    }
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_pressed(sfKeyEvent evt)
{
    handle_editor_key_prop_movement(evt);
    handle_editor_key_delete(evt);
    handle_editor_key_copy_paste(evt);
    handle_editor_key_animation(evt);
    handle_editor_key_canvas(evt);
}
