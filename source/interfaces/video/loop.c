/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void video_loop(void)
{
    ulong_t ems = (Time.currentTime - Engine.time);
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt))
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
    Engine.videoFrame = (uint_t)(((ems / VIDEO_FRAMERATE) %
        Engine.videoFrameCount));
    sfSprite_setTexture(Engine.sprite, Engine.frames[Engine.videoFrame],
        false);
    sfSprite_setScale(Engine.sprite, (v2f_t){Win.viewWidth / 1280.0f,
        Win.viewHeight / 720.0f});
    sfSprite_setPosition(Engine.sprite, PX_TO_MAPF(((v2f_t){0.0f, 0.0f})));
    sfRenderWindow_drawSprite(Win.self, Engine.sprite, NULL);
}
