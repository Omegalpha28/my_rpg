/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** load
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void load_video(cstring_t path, cstring_t soundName)
{
    warray_t ctn = my_dircontent(path);
    ulong_t len = my_walen(ctn);

    end_music();
    Engine.frames = (sfTexture **)malloc(sizeof(sfTexture *) * len);
    for (ulong_t i = 0; i < len; i++)
        Engine.frames[i] = i < 12 ? sfTexture_createFromFile(ctn[i], NULL)
            : NULL;
    Engine.frameLoaded = 11;
    Engine.content = ctn;
    update_time();
    Engine.videoFrame = 0;
    Engine.videoFrameCount = len;
    Engine.time = Time.currentTime;
    Engine.scene = SCENE_VIDEO;
    Engine.sprite = sfSprite_create();
    sfSprite_setPosition(Engine.sprite, PX_TO_MAPF(((v2f_t){0.0f, 0.0f})));
    Engine.music = find_music(soundName);
    sfMusic_play(Engine.music);
}
