/*
** EPITECH PROJECT, 2024
** moon-engine
** File description:
** main
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static void parse_events(sfEvent evt)
{
    if (evt.type == sfEvtClosed)
        sfRenderWindow_close(Win.self);
}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    sfEvent evt;

    init_time();
    create_window(0, 0, WIN_WINDOWED);
    while (sfRenderWindow_isOpen(Win.self)) {
        update_time();
        while (sfRenderWindow_pollEvent(Win.self, &evt))
            parse_events(evt);
        sfRenderWindow_clear(Win.self, sfWhite);
        sfRenderWindow_display(Win.self);
    }
    destroy_window();
    destroy_time();
    return (EXIT_SUCCESS);
}
