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

    Engine.debug.propDrawn = 0;
    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        parse_events(evt);
        if (evt.type == sfEvtKeyReleased &&
            evt.key.code == Setting.inventory.code)
            Engine.scene = SCENE_INVENTORY;
        if (evt.type == sfEvtKeyReleased &&
            evt.key.code == Setting.pause.code)
            Engine.scene = SCENE_PAUSE;
        CLICK_REL = click_rel(evt);
    }
    update();
    draw();
    update_hud();
    update_all_bullets();
    clear_entity_remove_queue();
}
