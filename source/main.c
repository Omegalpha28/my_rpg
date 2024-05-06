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
static void print_help(void)
{
    ulong_t n = 0;
    string_t buff = readf("help.info", &n);

    if (buff != NULL)
        my_putstr(buff);
    FREE(buff);
    sfRenderWindow_close(Win.self);
}

///////////////////////////////////////////////////////////////////////////////
static void check_program_flags(int argc, warray_t argv)
{
    if (argc == 1)
        return;
    if (WCMP(argv, "--editor") || WCMP(argv, "-e")) {
        load_zone("biome1");
        Editor.zone = Assets.zones[0];
        sfRenderWindow_setMouseCursorVisible(Win.self, true);
        Engine.scene = SCENE_LEVEL_EDITOR;
    }
    if (WCMP(argv, "--debug") || WCMP(argv, "-d"))
        Engine.debugMode = true;
    if (WCMP(argv, "--borderless") || WCMP(argv, "-b"))
        create_window(0, 0, WIN_BORDERLESS);
    if (WCMP(argv, "--fullscreen") || WCMP(argv, "-f"))
        create_window(0, 0, WIN_FULLSCREEN);
    if (WCMP(argv, "--windowed") || WCMP(argv, "-w"))
        create_window(0, 0, WIN_WINDOWED);
    if (WCMP(argv, "--help") || WCMP(argv, "-h"))
        print_help();
}

///////////////////////////////////////////////////////////////////////////////
static void switch_scene_loop(void)
{
    Setting.shoot = INVERT ? sfMouseRight : sfMouseLeft;
    if (Engine.scene == SCENE_MAIN_MENU)
        menu_loop();
    if (Engine.scene == SCENE_GAME)
        game_loop();
    if (Engine.scene == SCENE_SETTINGS)
        settings_loop();
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
    sfRenderWindow_setMouseCursorVisible(Win.self, false);
    check_program_flags(argc, argv);
    Player.ref = actor_create(Assets.creatures[CREATURE_PLAYER], V2F1(0.0f));
    level_load("tutorial/02");
    entity_create(Assets.creatures[CREATURE_ELITE_RACOON], V2F1(20.0f));
    while (sfRenderWindow_isOpen(Win.self)) {
        update_time();
        sfRenderWindow_clear(Win.self, EDITOR_BACKGROUND);
        switch_scene_loop();
        sfRenderWindow_display(Win.self);
    }
    destroy_window();
    destroy_assets();
    destroy_time();
    return (EXIT_SUCCESS);
}
