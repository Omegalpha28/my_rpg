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

static v2f_t input(v2f_t pos, float *sound, v2f_t max)
{
    float marge = 16.0f * Win.height / Win.viewHeight * 0.35f;
    v2i_t mouse = (sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.x > max.x - marge && mouse.y > pos.y - marge &&
        mouse.x < max.y + marge && mouse.y < pos.y + marge;
    sfBool press = sfMouse_isButtonPressed(Setting.shoot);

    RETURN(!mouse_in || !press, pos);
    pos.x = clampf(mouse.x, max.x, max.y);
    *sound = clampf((pos.x - max.x) / (max.y - max.x) * 100.0f, 0.0f, 100.0f);
    return pos;
}

static void draw_caret(v2f_t pos, float *sound, sfColor color, v2f_t max)
{
    sfSprite *caret = sfSprite_create();
    float marge = 16.0f * Win.height / Win.viewHeight * 0.35f / 2;

    pos.y += marge;
    pos = input(pos, sound, max);
    sfSprite_setTexture(caret, Assets.ui[UI_CARET]->self, false);
    sfSprite_setOrigin(caret, V2F(16.0f, 16.0f));
    sfSprite_rotate(caret, -45.0f);
    sfSprite_setColor(caret, color);
    sfSprite_setScale(caret, V2F1(0.5f));
    sfSprite_setPosition(caret, PX_TO_MAPF(pos));
    sfRenderWindow_drawSprite(Win.self, caret, false);
    sfSprite_destroy(caret);
}

static void draw_that_slide(v2f_t pos, bool_t color, float *sound)
{
    v2f_t size = {pos.x - Win.width / 8 * 5,
        16.0f * Win.height / Win.viewHeight * 0.35f};
    v2f_t size_caret = {size.x * (*sound) / 100.0f, size.y};
    sfColor colors = color ? sfColor_fromRGB(243, 199, 77) : sfWhite;
    v2f_t max;

    pos.x = Win.width / 2.0f + 120.0f * Win.width / Win.viewWidth * 0.35f;
    max = V2F(pos.x, pos.x + size.x);
    draw_rect(size, pos, sfColor_fromRGB(134, 127, 138));
    draw_rect(size_caret, pos, colors);
    draw_caret(V2F(pos.x + size_caret.x, pos.y), sound, colors, max);
}

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
    draw_that_slide(pos, mouse_in, sound);
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
