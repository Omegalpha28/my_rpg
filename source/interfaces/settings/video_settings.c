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

sfColor on_off(v2f_t pos, bool_t on)
{
    pos.x = Win.width / 8 * 5;
    draw_text(on ? "on" : "off", PX_TO_MAPF(pos), 0.35f, sfWhite);
    return sfWhite;
}

void draw_video(void)
{
    float scal = 4.0f * 16.0f * Win.height / Win.viewHeight * 0.35f;

    draw_text("Shake mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2)), 0.35F,
        on_off(V2F(Win.width / 4, Win.height / 2), true));
    draw_text("Blood mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal)), 0.35F,
        on_off(V2F(Win.width / 4, Win.height / 2 + scal), true));
    draw_text("Aimin mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal * 2)),
        0.35F, sfWhite);
    draw_text("Debug mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal * 3)),
        0.35F, on_off(V2F(Win.width / 4, Win.height / 2 + scal * 3), true));
}

/*
    draw_text("Resolution",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 3)),
        0.35F, sfWhite);
    draw_text("Windo mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 2)),
        0.35F, sfWhite);
    draw_text("Frame mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal)), 0.35F, sfWhite);


*/
