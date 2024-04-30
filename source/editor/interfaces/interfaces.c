/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** interfaces
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_editor_ui(void)
{
    draw_editor_settings();
    draw_editor_browser();
    draw_editor_bottom_bar();
    draw_editor_toolbar();
    for (uint_t i = 0; i < Editor.inputCount; i++)
        editor_draw_input(Editor.inputs[i]);
    draw_editor_context_menu();
}
