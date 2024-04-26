/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** bottom
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_editor_bottom_bar(void)
{
    char info[32];
    float fact = FACTORS(V2F1(20.0f)).x;
    float size = 16.0f * fact;

    draw_rect(V2F(Win.width - 450.0f, 32.0f), V2F(EDITOR_PANEL_W,
        Win.height - 32.0f), EDITOR_WIDGET);
    draw_text("Zone", PX_TO_MAPF(V2F(EDITOR_PANEL_W + 5.0f, Win.height -
        EDITOR_PANEL_H + 16.0f)), fact,
        RGB(200, 200, 200));
    draw_text(Editor.zone->name, add2f(PX_TO_MAPF(V2F(EDITOR_PANEL_W + 5.0f,
        Win.height - EDITOR_PANEL_H + 16.0f)), V2F((size - 2 * fact) * 5.0f,
        0.0f)), fact, RGB(200, 200, 0));
    snprintf(info, 32, "Scale x%.2f", Win.viewWidth / DEFAULT_VIEW_WIDTH);
    draw_text(info, PX_TO_MAPF(V2F(Win.width - EDITOR_PANEL_W - 200.0f,
        Win.height - EDITOR_PANEL_H + 16.0f)), fact, RGB(200, 200, 200));
}
