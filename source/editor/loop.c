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
    for (uint_t i = 0; Editor.bDisplay && i < Editor.bCount; i++)
        prop_draw(Editor.bProps[i]);
    actor_draw(Player.ref);
    for (uint_t i = 0; Editor.fDisplay && i < Editor.fCount; i++)
        prop_draw(Editor.fProps[i]);
    draw_editor_focus_hitbox();
    draw_editor_ui();
    Editor.oldMouse = Editor.crtMouse;
}
