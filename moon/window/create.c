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
    NULL,
    NULL,
    DEFAULT_WIDTH,
    DEFAULT_HEIGHT,
    DEFAULT_VIEW_WIDTH,
    DEFAULT_VIEW_HEIGHT,
    DEFAULT_MODE
};

///////////////////////////////////////////////////////////////////////////////
struct keybind_s Keys = {
    (key_track_t){DEFAULT_KEY_UP, false},
    (key_track_t){DEFAULT_KEY_DOWN, false},
    (key_track_t){DEFAULT_KEY_LEFT, false},
    (key_track_t){DEFAULT_KEY_RIGHT, false},
    (key_track_t){DEFAULT_KEY_RELOAD, false},
    (key_track_t){DEFAULT_KEY_HEAL, false},
    (key_track_t){DEFAULT_KEY_DASH, false},
    (key_track_t){DEFAULT_KEY_INTERACT, false},
    (key_track_t){DEFAULT_KEY_PAUSE, false},
    (key_track_t){DEFAULT_KEY_DANCE, false},
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
static void init_view(void)
{
    Win.viewWidth = DEFAULT_VIEW_WIDTH;
    Win.viewHeight = (float)((float)(DEFAULT_VIEW_WIDTH / (float)Win.width))
        * Win.height;
    sfView_setSize(Win.view, (v2f_t){Win.viewWidth, Win.viewHeight});
    sfView_setCenter(Win.view, (v2f_t){0, 0});
    sfRenderWindow_setView(Win.self, Win.view);
}

///////////////////////////////////////////////////////////////////////////////
bool_t create_window(uint_t width, uint_t height, int mode)
{
    sfVideoMode sc = sfVideoMode_getDesktopMode();
    sfVideoMode vm = {width, height, DEFAULT_BITS};

    if (!width || !height)
        vm = (sfVideoMode){DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_BITS};
    destroy_window();
    Win.width = mode == WIN_FULLSCREEN ? sc.width : vm.width;
    Win.height = mode == WIN_FULLSCREEN ? sc.height : vm.height;
    Win.view = sfView_create();
    Win.self = sfRenderWindow_create(vm, DEFAULT_TITLE, mode, NULL);
    if (!Win.view || !Win.self)
        return (false);
    init_view();
    sfRenderWindow_setFramerateLimit(Win.self, DEFAULT_FPS);
    sfRenderWindow_setPosition(Win.self, (v2i_t){MID(sc.width, Win.width),
        MID(sc.height, Win.height)});
    Win.mode = mode;
    return (set_window_icon());
}
