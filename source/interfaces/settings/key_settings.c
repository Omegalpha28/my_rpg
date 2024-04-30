/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** key_settings
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

static sfColor on_off(void)
{
    return sfWhite;
}

void draw_keybinds(void)
{
    float scal = 4.0f * 16.0f * Win.height / Win.viewHeight * 0.35f;

    draw_text("Invert clicks",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 3)),
        0.35F, on_off());
    draw_text("Sensitivity",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 2)),
        0.35F, sfWhite);
    draw_text("Change keybinds",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal)), 0.35F, sfWhite);
}
