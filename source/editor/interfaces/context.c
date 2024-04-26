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
static void draw_context_buttons(cstring_t str, v2f_t pos)
{
    float fact = FACTORS(V2F1(20.0f)).x;
    ulong_t len = strlen(str);
    float size = (16.0f * len);

    draw_rect(V2F(size + 20.0f, 32.0f), pos, EDITOR_BUTTON);
    draw_text(str, PX_TO_MAPF(add2f(pos, V2F(10.0f, 6.0f))), fact, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
void draw_editor_context_menu(void)
{
    draw_rect(V2F(Win.width, EDITOR_PANEL_H), V2F1(0.0f), EDITOR_WIDGET);
    draw_context_buttons("File", V2F(5.0f, 5.0f));
    draw_context_buttons("Edit", V2F(99.0f, 5.0f));
    draw_context_buttons("Select", V2F(193.0f, 5.0f));
    draw_context_buttons("View", V2F(319.0f, 5.0f));
    draw_context_buttons("Help", V2F(413.0f, 5.0f));
}
