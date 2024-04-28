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
    if (evt.code == sfKeyDelete)
        editor_delete();
    if (!(PRESSED(sfKeyLControl) || PRESSED(sfKeyRControl)))
        return;
    if (evt.code == sfKeyC)
        editor_copy();
    if (evt.code == sfKeyV)
        editor_paste();
    if (evt.code == sfKeyD)
        editor_duplicate();
    if (evt.code == sfKeyX)
        editor_cut();
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
static void handle_editor_key_layers(sfKeyEvent evt)
{
    if (evt.code == sfKeyF)
        Editor.layer = EDITOR_LAYER_FOREGROUND;
    if (evt.code == sfKeyB)
        Editor.layer = EDITOR_LAYER_BACKGROUND;
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_pressed(sfKeyEvent evt)
{
    handle_editor_key_prop_movement(evt);
    handle_editor_key_copy_paste(evt);
    handle_editor_key_animation(evt);
    handle_editor_key_canvas(evt);
    handle_editor_key_layers(evt);
}
