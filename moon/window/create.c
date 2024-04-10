/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** create
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
struct window_reference_s Win = {
    NULL, NULL, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_MODE
};

///////////////////////////////////////////////////////////////////////////////
struct keybind_s Keys = {
    DEFAULT_KEY_UP,
    DEFAULT_KEY_DOWN,
    DEFAULT_KEY_RIGHT,
    DEFAULT_KEY_LEFT,
    DEFAULT_KEY_RELOAD,
    DEFAULT_KEY_HEAL,
    DEFAULT_KEY_DASH,
    DEFAULT_KEY_INTERACT,
    DEFAULT_KEY_PAUSE,
    DEFAULT_KEY_SHOOT
};

///////////////////////////////////////////////////////////////////////////////
static bool_t set_window_icon(void)
{
    v2u_t size;
    sfImage *icn = sfImage_createFromFile(ASSETS DEFAULT_ICON);

    if (icn == NULL)
        return (true);
    size = sfImage_getSize(icn);
    sfRenderWindow_setIcon(Win.self, size.x, size.y,
        sfImage_getPixelsPtr(icn));
    sfImage_destroy(icn);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t create_window(uint_t width, uint_t height, int mode)
{
    sfVideoMode sc = sfVideoMode_getDesktopMode();
    sfVideoMode vm = {width, height, DEFAULT_BITS};

    if (!width || !height)
        vm = (sfVideoMode){DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_BITS};
    destroy_window();
    Win.view = sfView_create();
    Win.self = sfRenderWindow_create(vm, DEFAULT_TITLE, mode, NULL);
    if (!Win.view || !Win.self)
        return (false);
    sfView_setSize(Win.view, (v2f_t){DEFAULT_VIEW_WIDTH, DEFAULT_VIEW_HEIGHT});
    sfView_setCenter(Win.view, (v2f_t){DEFAULT_VIEW_WIDTH / 2.f,
        DEFAULT_VIEW_HEIGHT / 2.f});
    sfRenderWindow_setView(Win.self, Win.view);
    sfRenderWindow_setFramerateLimit(Win.self, DEFAULT_FPS);
    sfRenderWindow_setPosition(Win.self, (v2i_t){MID(sc.width, Win.width),
        MID(sc.height, Win.height)});
    Win.mode = mode;
    return (set_window_icon());
}
