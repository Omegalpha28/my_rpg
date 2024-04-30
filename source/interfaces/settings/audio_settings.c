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

void draw_audio(void)
{
    float scal = 5.5f * 16.0f * Win.height / Win.viewHeight * 0.35f;

    draw_text("Master sound",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal)), 0.35F, sfWhite);
    draw_text("Music sound",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2)), 0.35F, sfWhite);
    draw_text("Sound effects",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal)), 0.35F, sfWhite);
}
