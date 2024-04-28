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
static void switch_scene_loop(void)
{
    if (Engine.scene == SCENE_MAIN_MENU)
        menu_loop();
    if (Engine.scene == SCENE_GAME)
        game_loop();
    if (Engine.scene == SCENE_LEVEL_EDITOR)
        editor_loop();
    if (Engine.scene == SCENE_VIDEO)
        video_loop();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, warray_t argv)
{
    srand((unsigned)time(NULL));
    if (!init_time() || !init_assets() || !create_window(0, 0, WIN_FULLSCREEN))
        return (EXIT_FAILURE);
    check_program_flags(argc, argv);
    Player.ref = actor_create(Assets.creatures[CREATURE_PLAYER], V2F1(0.0f));
    while (sfRenderWindow_isOpen(Win.self)) {
        update_time();
        sfRenderWindow_clear(Win.self, EDITOR_BACKGROUND);
        switch_scene_loop();
        sfRenderWindow_display(Win.self);
    }
    destroy_window();
    destroy_time();
    return (EXIT_SUCCESS);
}
