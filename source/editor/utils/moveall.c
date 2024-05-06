/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** moveall
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void editor_moveall(int x, int y)
{
    for (uint_t i = 0; i < Editor.fCount; i++) {
        Editor.fProps[i]->position = add2f(Editor.fProps[i]->position,
            V2F(x, y));
        prop_set_transform(Editor.fProps[i]);
    }
    for (uint_t i = 0; i < Editor.bCount; i++) {
        Editor.bProps[i]->position = add2f(Editor.bProps[i]->position,
            V2F(x, y));
        prop_set_transform(Editor.bProps[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
void editor_moveall_up(void)
{
    editor_moveall(0, -1);
}

///////////////////////////////////////////////////////////////////////////////
void editor_moveall_down(void)
{
    editor_moveall(0, 1);
}

///////////////////////////////////////////////////////////////////////////////
void editor_moveall_left(void)
{
    editor_moveall(-1, 0);
}

///////////////////////////////////////////////////////////////////////////////
void editor_moveall_right(void)
{
    editor_moveall(1, 0);
}
