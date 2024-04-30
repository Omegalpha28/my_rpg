/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** audio_settings
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

sfColor slide(v2f_t pos, float *sound)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.x > PX_TO_MAPF(V2F1(pos.x - marge)).x &&
        mouse.x < PX_TO_MAPF(V2F1(Win.width / 4 * 3 + marge)).x &&
        mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y;
    char buff[8];

    pos.x = Win.width / 4 * 3;
    snprintf(buff, 8, "%.1f%%", *sound);
    draw_text(buff, PX_TO_MAPF(pos), 0.35f,
        (mouse_in ? sfColor_fromRGB(243, 199, 77) : sfWhite));
    RETURN(!mouse_in, sfWhite);
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}

void draw_audio(void)
{
    float scal = 5.5f * 16.0f * Win.height / Win.viewHeight * 0.35f;

    draw_text("Master sound",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal)), 0.35F,
        slide(V2F(Win.width / 4, Win.height / 2 - scal), &Setting.master));
    draw_text("Music sound",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2)), 0.35F,
        slide(V2F(Win.width / 4, Win.height / 2), &Setting.music));
    draw_text("Sound effects",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal)), 0.35F,
        slide(V2F(Win.width / 4, Win.height / 2 + scal), &Setting.sound));
}
