/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void update(void)
{
    player_movement();
    update_entity();
    update_collisions();
    update_shaking();
    cursor_focus();
    check_level_end();
}

///////////////////////////////////////////////////////////////////////////////
void game_loop(void)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt))
        parse_events(evt);
    update();
    draw();
    update_all_bullets();
    clear_entity_remove_queue();
}
