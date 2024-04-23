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
    Player.ref = actor_create(Assets.creatures[CREATURE_PLAYER], V2F1(0.0f));
    while (sfRenderWindow_isOpen(Win.self)) {
        update_time();
        sfRenderWindow_clear(Win.self, EDITOR_BACKGROUND);
        if (Engine.scene == SCENE_GAME)
            game_loop();
        if (Engine.scene == SCENE_LEVEL_EDITOR)
            editor_loop();
        if (Engine.scene == SCENE_VIDEO)
            video_loop();
        sfRenderWindow_display(Win.self);
    }
    destroy_window();
    destroy_time();
    return (EXIT_SUCCESS);
}
