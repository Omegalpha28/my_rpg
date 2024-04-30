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
static bool_t check_end(bool_t force)
{
    if (!force && Engine.frames[Engine.videoFrame] != NULL)
        return (false);
    for (uint_t i = 0; i < Engine.videoFrameCount; i++) {
        if (Engine.frames[i] == NULL)
            continue;
        sfTexture_destroy(Engine.frames[i]);
    }
    Engine.scene = SCENE_MAIN_MENU;
    FREE(Engine.frames);
    Engine.frames = NULL;
    Engine.frameLoaded = 0;
    if (Engine.sprite != NULL)
        sfSprite_destroy(Engine.sprite);
    Engine.time = 0;
    Engine.sprite = NULL;
    Engine.videoFrame = 0;
    my_watroy(Engine.content);
    sfMusic_stop(Engine.music);
    Engine.content = NULL;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t handle_video_events(void)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
        if (evt.type == sfEvtKeyReleased && evt.key.code >= sfKeySpace)
            return (check_end(true));
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
static void load_next_video_frame(void)
{
    if (Engine.frameLoaded < Engine.videoFrameCount) {
        Engine.frames[Engine.frameLoaded] = sfTexture_createFromFile(
            Engine.content[Engine.frameLoaded], NULL);
        Engine.frameLoaded++;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void draw_skip_button(void)
{
    sfSprite *btn = sfSprite_create();

    sfSprite_setTexture(btn, Assets.ui[UI_BUTTONS]->self, false);
    sfSprite_setTextureRect(btn, (recti_t){22, 16, 18, 12});
    draw_text("Skip", PX_TO_MAPF(V2F(Win.width - 265.0f, Win.height - 100.0f)),
        FACTORS(V2F1(20.0f)).x * 2.0f, WHITE);
    sfSprite_setScale(btn, V2F1(0.8f));
    sfSprite_setPosition(btn, PX_TO_MAPF(V2F(Win.width - 120.0f,
        Win.height - 100.0f)));
    sfRenderWindow_drawSprite(Win.self, btn, NULL);
    sfSprite_destroy(btn);
}

///////////////////////////////////////////////////////////////////////////////
void video_loop(void)
{
    ulong_t ems = (Time.currentTime - Engine.time);
    uint_t frame = (((ems / VIDEO_FRAMERATE) % Engine.videoFrameCount));

    if (handle_video_events())
        return;
    if (frame != Engine.videoFrame && Engine.frames[Engine.videoFrame]) {
        sfTexture_destroy(Engine.frames[Engine.videoFrame]);
        Engine.frames[Engine.videoFrame] = NULL;
    }
    Engine.videoFrame = frame;
    if (check_end(false))
        return;
    sfSprite_setTexture(Engine.sprite, Engine.frames[Engine.videoFrame],
        false);
    sfSprite_setScale(Engine.sprite, (v2f_t){Win.viewWidth / 1280.0f,
        Win.viewHeight / 720.0f});
    sfSprite_setPosition(Engine.sprite, PX_TO_MAPF(((v2f_t){0.0f, 0.0f})));
    sfRenderWindow_drawSprite(Win.self, Engine.sprite, NULL);
    draw_skip_button();
    load_next_video_frame();
}
