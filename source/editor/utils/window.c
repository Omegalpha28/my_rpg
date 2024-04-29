/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** context
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void editor_hide_context(void)
{
    for (uint_t i = 0; i < CONTEXT_COUNT; i++)
        CONTEXTS[i].expand = false;
}

///////////////////////////////////////////////////////////////////////////////
void editor_switch_foreground(void)
{
    Editor.fDisplay = !Editor.fDisplay;
}

///////////////////////////////////////////////////////////////////////////////
void editor_switch_background(void)
{
    Editor.bDisplay = !Editor.bDisplay;
}

///////////////////////////////////////////////////////////////////////////////
void editor_return_menu(void)
{
    if (Editor.zone != NULL)
        unload_zone(Editor.zone->name);
    editor_reset();
    Engine.scene = SCENE_MAIN_MENU;
    sfMouse_setPositionRenderWindow(V2I(Win.width / 2, Win.height / 2),
        Win.self);
    sfRenderWindow_setMouseCursorVisible(Win.self, false);
}
