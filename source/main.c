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
static void check_program_flags(int argc, warray_t argv)
{
    if (argc == 1)
        return;
    if (WCMP(argv, "--editor") || WCMP(argv, "-e")) {
        load_zone("biome1");
        Editor.zone = Assets.zones[0];
        Engine.scene = SCENE_LEVEL_EDITOR;
    }
    if (WCMP(argv, "--debug") || WCMP(argv, "-d"))
        Engine.debugMode = true;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, warray_t argv)
{
    srand((unsigned)time(NULL));
    if (!init_time() || !init_assets() || !create_window(0, 0, WIN_WINDOWED))
        return (EXIT_FAILURE);
    Player.ref = actor_create(Assets.creatures[CREATURE_PLAYER], V2F1(0.0f));
    check_program_flags(argc, argv);
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
