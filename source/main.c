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
    if (Engine.scene == SCENE_SAVES)
        saves_loop();
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
