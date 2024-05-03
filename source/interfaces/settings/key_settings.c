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

sfColor draw_keys(v2f_t pos)
{
    float scal = 16.0f * Win.height / Win.viewHeight * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.x > PX_TO_MAPF(V2F1(pos.x - scal)).x &&
        mouse.x < PX_TO_MAPF(V2F1(Win.width / 8 * 5 + scal * 10)).x &&
        mouse.y > PX_TO_MAPF(V2F1(pos.y - scal)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + scal * 25)).y;

    RETURN(!mouse_in, sfWhite);
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}

void draw_keybinds(void)
{
    float scal = 4.0f * 16.0f * Win.height / Win.viewHeight * 0.35f;

    draw_text("Invert click",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 3)),
        0.35F, on_off(V2F(Win.width / 4, Win.height / 2 - scal * 3), &INVERT));
    draw_text("Change keybinds",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 2)), 0.35F,
        draw_keys(V2F(Win.width / 4, Win.height / 2 - scal * 2)));
}
