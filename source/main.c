/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** main
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    sfEvent evt;

    if (!init_time() || !init_assets() || !create_window(0, 0, WIN_WINDOWED))
        return (EXIT_FAILURE);
    Player.ref = actor_create(Assets.creatures[0], (v2f_t){0, 0});
    actor_set_variant(Player.ref, "debug", 0);
    while (sfRenderWindow_isOpen(Win.self)) {
        update_time();
        while (sfRenderWindow_pollEvent(Win.self, &evt))
            parse_events(evt);
        sfRenderWindow_clear(Win.self, sfWhite);
        game_loop();
        sfRenderWindow_display(Win.self);
    }
    destroy_window();
    destroy_time();
    return (EXIT_SUCCESS);
}
