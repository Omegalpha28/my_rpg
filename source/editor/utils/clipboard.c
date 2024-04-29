/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** clipboard
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void editor_copy(void)
{
    if (!Editor.focus)
        return;
    Editor.copy = Editor.focus->self;
    if (Editor.hover)
        editor_hide_context();
}

///////////////////////////////////////////////////////////////////////////////
void editor_paste(void)
{
    prop_t ***arr = Editor.layer == EDITOR_LAYER_FOREGROUND ?
        &(Editor.fProps) : &(Editor.bProps);
    uint_t *counter = Editor.layer == EDITOR_LAYER_FOREGROUND ?
        &(Editor.fCount) : &(Editor.bCount);
    v2f_t pos = Editor.hover ? PX_TO_MAPF(V2F(Win.width / 2.0f,
        Win.height / 2.0f)) : Editor.crtMouse;

    if (!Editor.copy)
        return;
    add_prop(Editor.copy, arr, counter);
    (*arr)[(*counter) - 1]->position.x = floorf(pos.x);
    (*arr)[(*counter) - 1]->position.y = floorf(pos.y);
    prop_set_transform((*arr)[(*counter) - 1]);
    Editor.focus = (*arr)[(*counter) - 1];
    if (Editor.hover)
        editor_hide_context();
}

///////////////////////////////////////////////////////////////////////////////
void editor_cut(void)
{
    editor_copy();
    editor_delete();
}

///////////////////////////////////////////////////////////////////////////////
void editor_duplicate(void)
{
    editor_copy();
    editor_paste();
}

///////////////////////////////////////////////////////////////////////////////
void editor_delete(void)
{
    if (!Editor.focus)
        return;
    remove_prop(Editor.focus, &(Editor.fProps), &(Editor.fCount));
    remove_prop(Editor.focus, &(Editor.bProps), &(Editor.bCount));
    Editor.focus = NULL;
    if (Editor.hover)
        editor_hide_context();
    input_clear(Editor.inputs[EDITOR_INPUT_X]);
    input_clear(Editor.inputs[EDITOR_INPUT_Y]);
}
