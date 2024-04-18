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

    if (Editor.focus && ((evt.code == sfKeyC || evt.code == sfKeyD) && ctrl))
        Editor.copy = Editor.focus;
    if ((Editor.copy && (evt.code == sfKeyV && ctrl)) || (Editor.focus &&
        (evt.code == sfKeyD && ctrl))) {
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
static void handle_editor_key_delete(sfKeyEvent evt)
{
    if (Editor.focus && (evt.code == sfKeyDelete)) {
        remove_prop(Editor.focus, &(Editor.fProps), &(Editor.fCount));
        remove_prop(Editor.focus, &(Editor.bProps), &(Editor.bCount));
        Editor.focus = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_tests(sfKeyEvent evt)
{
    int l = rand() % 2 ? true : false;
    int c = rand() % Editor.zone->categoryCount;
    int s = rand() % Editor.zone->categories[c]->sheetCount;

    if (evt.code == sfKeyNumpad0)
        level_save("test_level.lvl");
    if (evt.code == sfKeyNumpad2)
        level_load("test_level.lvl");
    if (evt.code == sfKeyAdd) {
        add_prop(Editor.zone->categories[c]->sheets[s],
            l ? &(Editor.fProps) : &(Editor.bProps),
            l ? &(Editor.fCount) : &(Editor.bCount));
    }
    if (evt.code == sfKeyNum0)
        Editor.bDisplay = !Editor.bDisplay;
    if (evt.code == sfKeyNum1)
        Editor.fDisplay = !Editor.fDisplay;
}

///////////////////////////////////////////////////////////////////////////////
static void handle_editor_key_animation(sfKeyEvent evt)
{
    if (Editor.focus && evt.code == sfKeySpace)
        prop_animate(Editor.focus);
}

///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_pressed(sfKeyEvent evt)
{
    handle_editor_key_prop_movement(evt);
    handle_editor_key_copy_paste(evt);
    handle_editor_key_delete(evt);
    handle_editor_key_animation(evt);
    handle_editor_key_tests(evt);
}
