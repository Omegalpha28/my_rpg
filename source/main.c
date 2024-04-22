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
    srand((unsigned)time(NULL));
    if (!init_time() || !init_assets() || !create_window(0, 0, WIN_WINDOWED))
        return (EXIT_FAILURE);
    Player.ref = actor_create(Assets.creatures[creaturePlayer], (v2f_t){0, 0});
    //entity_create(Assets.creatures[creatureDuck], (v2f_t){10, 10});
    Engine.scene = sceneLevelEditor;
    Editor.zone = Assets.zones[0];
    load_zone("biome1");
    while (sfRenderWindow_isOpen(Win.self)) {
        update_time();
        sfRenderWindow_clear(Win.self, sfWhite);
        if (Engine.scene == sceneGame)
            game_loop();
        if (Engine.scene == sceneLevelEditor)
            editor_loop();
        sfRenderWindow_display(Win.self);
    }
    destroy_window();
    destroy_time();
    return (EXIT_SUCCESS);
}
