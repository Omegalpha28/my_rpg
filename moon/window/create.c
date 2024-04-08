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
static bool set_window_icon(void)
{
    v2u size;
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
bool create_window(uint width, uint height, int mode)
{
    sfVideoMode sc = sfVideoMode_getDesktopMode();
    sfVideoMode vm = {width, height, DEFAULT_BITS};

    if (!width || !height) {
        vm.width = DEFAULT_WIDTH;
        vm.height = DEFAULT_HEIGHT;
    }
    destroy_window();
    Win.view = sfView_create();
    Win.self = sfRenderWindow_create(vm, DEFAULT_TITLE, mode, NULL);
    if (!Win.view || !Win.self)
        return (false);
    sfRenderWindow_setView(Win.self, Win.view);
    sfView_setCenter(Win.view, (v2f){DEFAULT_VIEW_WIDTH / 2.f,
        DEFAULT_VIEW_HEIGHT / 2.f});
    sfRenderWindow_setFramerateLimit(Win.self, DEFAULT_FPS);
    sfRenderWindow_setPosition(Win.self, (v2i){MID(sc.width, Win.width),
        MID(sc.height, Win.height)});
    Win.mode = mode;
    return (set_window_icon());
}
