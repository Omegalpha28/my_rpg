/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** resolution
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

static ulong_t get_index(void)
{
    ulong_t i = 0;

    for (; i < Setting.modesCunt; i++)
        if (Setting.modes[i].width == Win.width &&
            Setting.modes[i].height == Win.height)
            return i;
    return 0;
}

static bool_t video_not_good(ulong_t index)
{
    if (Setting.modes[index].bitsPerPixel != 32 ||
        Setting.modes[index].width < 800 ||
        Setting.modes[index].height < 600 ||
        Setting.modes[index].width / Setting.modes[index].height != 16 / 9 ||
        Setting.modes[index].width / Setting.modes[index].height != 16 / 10)
        return true;
    return false;
}

static void change_relay(ulong_t index, bool_t mouse_y)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    if (mouse.x > PX_TO_MAPF(V2F1(Win.width / 8 * 5 + marge * 11)).x &&
        mouse.x < PX_TO_MAPF(V2F1(Win.width / 8 * 5 + marge * 13)).x &&
        mouse_y && index > 0 && Win.mode != WIN_FULLSCREEN) {
        index--;
        while (index > 0 && video_not_good(index))
            index--;
        create_window(Setting.modes[index].width, Setting.modes[index].height,
            Win.mode);
        }
}

static void click_change(ulong_t index, v2f_t pos)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_y = mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        CLICK_REL && mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y &&
        index < Setting.modesCunt;

    if (mouse.x > PX_TO_MAPF(V2F1(Win.width / 8 * 5 - marge * 4)).x &&
        mouse.x < PX_TO_MAPF(V2F1(Win.width / 8 * 5 - marge * 2)).x &&
        mouse_y && index < Setting.modesCunt && Win.mode != WIN_FULLSCREEN) {
        index++;
        while (index < Setting.modesCunt && video_not_good(index))
            index++;
        create_window(Setting.modes[index].width, Setting.modes[index].height,
            Win.mode);
    }
    change_relay(index, mouse_y);
}

static bool_t inbounds(v2f_t pos, v2f_t x)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    return (mouse.y > PX_TO_MAPF(V2F1(pos.y - marge)).y &&
        mouse.y < PX_TO_MAPF(V2F1(pos.y + marge * 2)).y &&
        mouse.x > PX_TO_MAPF(V2F1(x.x)).x &&
        mouse.x < PX_TO_MAPF(V2F1(x.y)).x);
}

void draw_button_relay(v2f_t pos, sfSprite *arrow, ulong_t index_reso)
{
    sfIntRect rect = {0, 0, 16, 16};
    bool_t low = !index_reso || Win.mode == WIN_FULLSCREEN;
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    sfColor col = inbounds(pos, V2F(Win.width / 8 * 5 + marge * 11,
        Win.width / 8 * 5 + marge * 13)) ?
        sfColor_fromRGB(243, 199, 77) : sfWhite;

    rect.left = 48;
    sfSprite_setTextureRect(arrow, rect);
    sfSprite_setPosition(arrow, PX_TO_MAPF(V2F(Win.width / 8 * 5 + marge * 12,
        pos.y + marge * 0.5f)));
    sfSprite_setColor(arrow, low ? sfColor_fromRGB(53, 49, 46) : col);
    sfRenderWindow_drawSprite(Win.self, arrow, false);
    sfSprite_destroy(arrow);
    click_change(index_reso, pos);
}

void draw_button_arrow(v2f_t pos)
{
    ulong_t index_reso = get_index();
    bool_t high = index_reso == Setting.modesCunt ||
        Win.mode == WIN_FULLSCREEN;
    sfSprite *arrow = sfSprite_create();
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    sfIntRect rect = {0, 0, 16, 16};
    sfColor col = inbounds(pos, V2F(Win.width / 8 * 5 - marge * 4,
        Win.width / 8 * 5 - marge * 2)) ?
        sfColor_fromRGB(243, 199, 77) : sfWhite;

    sfSprite_setTexture(arrow, Assets.ui[UI_ARROWS]->self, false);
    sfSprite_setTextureRect(arrow, rect);
    sfSprite_setScale(arrow, V2F1(0.75f));
    sfSprite_setOrigin(arrow, V2F(8.0f, 8.0f));
    sfSprite_setPosition(arrow, PX_TO_MAPF(V2F(Win.width / 8 * 5 - marge * 3,
        pos.y + marge * 0.5f)));
    sfSprite_setColor(arrow, high ? sfColor_fromRGB(53, 49, 46) : col);
    sfRenderWindow_drawSprite(Win.self, arrow, false);
    draw_button_relay(pos, arrow, index_reso);
}

sfColor resolu(v2f_t pos)
{
    float marge = 1.0f * 16.0f * Win.width / Win.viewWidth * 0.35f;
    bool_t mouse_in = inbounds(pos, V2F(pos.x -marge,
        Win.width / 8 * 5 + marge * 24));
    char buff[5];
    sfColor col = mouse_in ? sfColor_fromRGB(243, 199, 77) : sfWhite;

    snprintf(buff, 5, "%u", Win.width);
    draw_text_center(buff, V2F(Win.width / 8 * 5 + marge, pos.y), 0.35f,
        Win.mode == WIN_FULLSCREEN ? sfColor_fromRGB(53, 49, 46) : col);
    snprintf(buff, 5, "%u", Win.height);
    draw_text_center(buff, V2F(Win.width / 8 * 5 + marge * 8.0, pos.y), 0.35f,
        Win.mode == WIN_FULLSCREEN ? sfColor_fromRGB(53, 49, 46) : col);
    draw_text_center("x", V2F(Win.width / 8 * 5 + marge * 4.5, pos.y), 0.35f,
        Win.mode == WIN_FULLSCREEN ? sfColor_fromRGB(53, 49, 46) : col);
    draw_button_arrow(pos);
    RETURN(!mouse_in, sfWhite);
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}
