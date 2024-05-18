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
        mouse.x < PX_TO_MAPF(V2F1(Win.width / 8 * 5 + marge * 10)).x &&
        mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y;
    sfColor color = (*on ? sfWhite : sfColor_fromRGB(53, 49, 46));

    pos.x = Win.width / 8 * 5 + marge * 4.5;
    draw_text_center(*on ? "on" : "off", pos, 0.35f,
        (mouse_in ? sfColor_fromRGB(243, 199, 77) : color));
    RETURN(!mouse_in, sfWhite);
    if (CLICK_REL && mouse_in)
        *on = !(*on);
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}

static void change_window(v2f_t pos, bool_t mouse_y)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    int mod = Win.mode;

    if (mouse.x > PX_TO_MAPF(V2F1(pos.x - marge * 13)).x && mouse_y &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge)).x && mod != WIN_BORDERLESS &&
        CLICK_REL)
        create_window(0, 0, WIN_BORDERLESS);
    if (mouse.x > PX_TO_MAPF(V2F1(pos.x - marge * 0.5)).x && mouse_y &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge * 9.5)).x && CLICK_REL &&
        mod != WIN_WINDOWED)
        create_window(0, 0, WIN_WINDOWED);
    if (mouse.x > PX_TO_MAPF(V2F1(pos.x + marge * 8.5)).x && mouse_y &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge * 20.5)).x && CLICK_REL &&
        mod != WIN_FULLSCREEN)
        create_window(0, 0, WIN_FULLSCREEN);
    sfRenderWindow_setMouseCursorVisible(Win.self, false);
}

static void change_framerate(v2f_t pos, uint_t *val, bool_t y)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    if (mouse.x > PX_TO_MAPF(V2F1(pos.x - marge * 13.5)).x && y && CLICK_REL &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x - marge * 6.5)).x && *val != 30)
        *val = 30;
    if (mouse.x > PX_TO_MAPF(V2F1(pos.x - marge * 1.5)).x && y && *val != 60 &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge * 3.5)).x && CLICK_REL)
        *val = 60;
    if (mouse.x > PX_TO_MAPF(V2F1(pos.x + marge * 5.5)).x && y && CLICK_REL &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge * 13.5)).x && *val != 120)
        *val = 120;
    if (mouse.x > PX_TO_MAPF(V2F1(pos.x + marge * 17)).x && y && CLICK_REL &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge * 22)).x && *val <= 120)
        *val = 9999;
}

static void change_aim(v2f_t pos, uint_t *val, bool_t y)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    if (mouse.x > PX_TO_MAPF(V2F1(pos.x - marge * 13)).x && y &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge)).x && CLICK_REL && *val != 0)
        *val = 0;
    if (mouse.x > PX_TO_MAPF(V2F1(pos.x - marge * 0.5)).x && y && *val != 5 &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge * 9.5)).x && CLICK_REL)
        *val = 5;
    if (mouse.x > PX_TO_MAPF(V2F1(pos.x + marge * 8.5)).x && y && CLICK_REL &&
        mouse.x < PX_TO_MAPF(V2F1(pos.x + marge * 20.5)).x && *val != 10)
        *val = 10;
}

void draw_all_next(int count, uint_t *val, sfColor col, v2f_t pos)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_y = mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y;

    if (count == 3) {
        draw_text_center("None", V2F(pos.x - marge * 6, pos.y), 0.35f,
            (*val == 0 ? sfColor_fromRGB(53, 49, 46) : col));
        draw_text_center("Medium", V2F(pos.x + marge * 4.5, pos.y), 0.35f,
            (*val == 5 ? sfColor_fromRGB(53, 49, 46) : col));
        draw_text_center("Cheat", V2F(pos.x + marge * 14.5, pos.y), 0.35f,
            (*val == 10 ? sfColor_fromRGB(53, 49, 46) : col));
        change_aim(pos, val, mouse_y);
        return;
    }
}

static void draw_all_relay(int count, uint_t *val, sfColor col, v2f_t pos)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_y = mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y;

    if (count == 2) {
        draw_text("30fps", PX_TO_MAPF(V2F(pos.x - marge * 12.5, pos.y)), 0.35f,
            (*val == 30 ? sfColor_fromRGB(53, 49, 46) : col));
        draw_text("60fps", PX_TO_MAPF(V2F(pos.x - marge * 2.5, pos.y)), 0.35f,
            (*val == 60 ? sfColor_fromRGB(53, 49, 46) : col));
        draw_text("120fps", PX_TO_MAPF(V2F(pos.x + marge * 6.5, pos.y)), 0.35f,
            (*val == 120 ? sfColor_fromRGB(53, 49, 46) : col));
        draw_text("max", PX_TO_MAPF(V2F(pos.x + marge * 18, pos.y)), 0.35f,
            (*val > 120 ? sfColor_fromRGB(53, 49, 46) : col));
        change_framerate(pos, val, mouse_y);
        return;
    }
    draw_all_next(count, val, col, pos);
}

static void draw_all(int count, uint_t *val, v2f_t pos, bool_t mouse_in)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    sfColor col = (mouse_in ? sfColor_fromRGB(243, 199, 77) : sfWhite);
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_y = mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y;

    if (count == 1) {
        draw_text_center("Borderless", V2F(pos.x - marge * 6, pos.y), 0.35f,
            (Win.mode == WIN_BORDERLESS ? sfColor_fromRGB(53, 49, 46) : col));
        draw_text_center("Windowed", V2F(pos.x + marge * 4.5, pos.y), 0.35f,
            (Win.mode == WIN_WINDOWED ? sfColor_fromRGB(53, 49, 46) : col));
        draw_text_center("Fullscreen", V2F(pos.x + marge * 14.5, pos.y), 0.35f,
            (Win.mode == WIN_FULLSCREEN ? sfColor_fromRGB(53, 49, 46) : col));
        change_window(pos, mouse_y);
        return;
    }
    draw_all_relay(count, val, col, pos);
}

sfColor choices(v2f_t pos, uint_t *val, int count)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.x > PX_TO_MAPF(V2F1(pos.x - marge)).x &&
        mouse.x < PX_TO_MAPF(V2F1(Win.width / 8 * 5 + marge * 24)).x &&
        mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y;

    draw_all(count, val, V2F(Win.width / 8 * 5, pos.y), mouse_in);
    RETURN(!mouse_in, sfWhite);
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}

void draw_video_relay(float scal)
{
    draw_text("Shake mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2)), 0.35F,
        on_off(V2F(Win.width / 4, Win.height / 2), &SHAKE));
    draw_text("Blood mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal)), 0.35F,
        on_off(V2F(Win.width / 4, Win.height / 2 + scal), &BLOOD));
    draw_text("Aimin mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 + scal * 2)), 0.35F,
        choices(V2F(Win.width / 4, Win.height / 2 + scal * 2), &AIMING, 3));
}

void draw_video(void)
{
    float scal = 4.0f * 16.0f * Win.height / Win.viewHeight * 0.35f;

    draw_text("Resolution",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 3)),
        0.35F, resolu(V2F(Win.width / 4, Win.height / 2 - scal * 3)));
    draw_text("Windo mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal * 2)),
        0.35F, choices(V2F(Win.width / 4, Win.height / 2 - scal * 2),
        &WIN_MODES, 1));
    draw_text("Frame mode",
        PX_TO_MAPF(V2F(Win.width / 4, Win.height / 2 - scal)), 0.35F,
        choices(V2F(Win.width / 4, Win.height / 2 - scal), &FRAMERATE, 2));
    draw_video_relay(scal);
}
