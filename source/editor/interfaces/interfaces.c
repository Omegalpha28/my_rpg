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
    draw_rect(V2F(EDITOR_PANEL_W, Win.height - EDITOR_PANEL_H * 2),
        V2F(Win.width - EDITOR_PANEL_W, EDITOR_PANEL_H * 2), EDITOR_WIDGET);
    draw_editor_browser();
    draw_editor_bottom_bar();
    draw_rect(V2F(Win.width, EDITOR_PANEL_H), V2F(0.0f, EDITOR_PANEL_H),
        EDITOR_WIDGET);
    draw_editor_context_menu();
}
