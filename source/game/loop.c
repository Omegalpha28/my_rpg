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
    cursor_focus();
    bullet_update();
    update_shaking();
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
    clear_entity_remove_queue();
}
