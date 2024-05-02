/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** video_settings
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

sfColor on_off(v2f_t pos, bool_t *on)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.x > PX_TO_MAPF(V2F1(pos.x - marge)).x &&
        mouse.x < PX_TO_MAPF(V2F1(Win.width / 8 * 5 + marge * 4)).x &&
        mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y;
    sfColor color = (*on ? sfWhite : sfColor_fromRGB(53, 49, 46));

    pos.x = Win.width / 8 * 5;
    draw_text(*on ? "on" : "off", PX_TO_MAPF(pos), 0.35f,
        (mouse_in ? sfColor_fromRGB(243, 199, 77) : color));
    RETURN(!mouse_in, sfWhite);
    if (CLICK_REL)
        *on = !(*on);
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}

void draw_video(void)
{
    float scal = 4.0f * 16.0f * Win.height / Win.viewHeight * 0.35f;

    draw_text("Resolution",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 3)),
        0.35F, sfWhite);
    draw_text("Windo mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 2)),
        0.35F, sfWhite);
    draw_text("Frame mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal)), 0.35F, sfWhite);
    draw_text("Shake mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2)), 0.35F,
        on_off(V2F(Win.width / 4, Win.height / 2), &SHAKE));
    draw_text("Blood mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal)), 0.35F,
        on_off(V2F(Win.width / 4, Win.height / 2 + scal), &BLOOD));
    draw_text("Aimin mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal * 2)),
        0.35F, sfWhite);
}
