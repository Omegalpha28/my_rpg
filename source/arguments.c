/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** arguments
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
static void check_full_flag(int argc, warray_t argv, uint_t *i)
{
    (argc) = (argc);
    if (CMP(argv[*(i)], "--borderless"))
        create_window(0, 0, WIN_BORDERLESS);
    if (CMP(argv[*(i)], "--fullscreen"))
        create_window(0, 0, WIN_FULLSCREEN);
    if (CMP(argv[*(i)], "--windowed"))
        create_window(0, 0, WIN_WINDOWED);
    if (CMP(argv[*(i)], "--debug"))
        Engine.debugMode = true;
    if (CMP(argv[*(i)], "--help"))
        print_help();
    if (CMP(argv[*(i)], "--editor")) {
        load_zone("biome1");
        Editor.zone = Assets.zones[0];
        sfRenderWindow_setMouseCursorVisible(Win.self, true);
        Engine.scene = SCENE_LEVEL_EDITOR;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void check_min_flag(int argc, warray_t argv, uint_t *i)
{
    ulong_t len = strlen(argv[*(i)]);

    for (ulong_t k = 1; k < len && argc > 1; k++) {
        if (argv[*(i)][k] == 'b')
            create_window(0, 0, WIN_BORDERLESS);
        if (argv[*(i)][k] == 'f')
            create_window(0, 0, WIN_FULLSCREEN);
        if (argv[*(i)][k] == 'w')
            create_window(0, 0, WIN_WINDOWED);
        if (argv[*(i)][k] == 'd')
            Engine.debugMode = true;
        if (argv[*(i)][k] == 'h')
            print_help();
        if (argv[*(i)][k] == 'e') {
            load_zone("biome1");
            Editor.zone = Assets.zones[0];
            sfRenderWindow_setMouseCursorVisible(Win.self, true);
            Engine.scene = SCENE_LEVEL_EDITOR;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void check_program_flags(int argc, warray_t argv)
{
    if (argc == 1)
        return;
    for (uint_t i = 1; i < (uint_t)argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == '-')
            check_full_flag(argc, argv, &(i));
        if (argv[i][0] == '-' && argv[i][1] != '-')
            check_min_flag(argc, argv, &(i));
    }
}
