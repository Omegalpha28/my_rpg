/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void editor_loop(void)
{
    sfEvent evt;

    draw_editor_map_border();
    Editor.crtMouse = sfRenderWindow_mapPixelToCoords(Win.self,
        sfMouse_getPositionRenderWindow(Win.self), Win.view);
    while (sfRenderWindow_pollEvent(Win.self, &evt))
        handle_editor_events(evt);
    if (Editor.bDisplay)
        draw_visible_props(Editor.bProps, Editor.bCount);
    actor_draw(Player.ref);
    if (Editor.fDisplay)
        draw_visible_props(Editor.fProps, Editor.fCount);
    draw_editor_focus_hitbox();
    draw_editor_ui();
    Editor.oldMouse = Editor.crtMouse;
}
