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
static void parse_events(sfEvent evt)
{
    if (evt.type == sfEvtClosed)
        sfRenderWindow_close(Win.self);
    if (evt.type == sfEvtKeyPressed && evt.key.code == sfKeyA) {
        if (Win.mode == WIN_FULLSCREEN)
            return ((void)(create_window(0, 0, WIN_BORDERLESS)));
        if (Win.mode == WIN_WINDOWED)
            return ((void)(create_window(0, 0, WIN_FULLSCREEN)));
        return ((void)(create_window(0, 0, WIN_WINDOWED)));
    }
    if (evt.type == sfEvtKeyPressed && evt.key.code == ALT_RIGHT)
        Pool.actors[0]->animId++;
}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    sfEvent evt;
    actor_t *act;

    if (!init_time() || !init_assets() || !create_window(0, 0, WIN_WINDOWED))
        return (EXIT_FAILURE);
    act = actor_create(Assets.creatures[0], (v2f_t){0, 0});
    actor_set_sheet(act, "adults");
    actor_set_variant(act, "debug", 0);
    actor_set_anim(act, "walk");
    while (sfRenderWindow_isOpen(Win.self)) {
        update_time();
        while (sfRenderWindow_pollEvent(Win.self, &evt))
            parse_events(evt);
        sfRenderWindow_clear(Win.self, sfWhite);
        actor_draw(act);
        sfRenderWindow_display(Win.self);
    }
    destroy_window();
    destroy_time();
    return (EXIT_SUCCESS);
}
