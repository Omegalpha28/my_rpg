/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** popup
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_editor_popup(void)
{
    v2f_t pos = V2F(Win.width / 2.0f - 225.0f, Win.height / 2.0f - 75.0f);

    draw_rect(V2F(Win.width, Win.height), V2F1(0.0f), RGBA(0, 0, 0, 100));
    draw_rect(V2F(450.0f, 150.0f), pos, EDITOR_WIDGET);
    draw_text(Editor.popupType == POPUP_SAVE ? "SAVE LEVEL" : "OPEN LEVEL",
        PX_TO_MAPF(add2f(pos, V2F1(10.0f))), FACTORS(V2F1(20.0f)).x, WHITE);
}
