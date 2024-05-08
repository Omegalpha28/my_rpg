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
static void draw_camera_bound(void)
{
    sfRectangleShape *cam = sfRectangleShape_create();

    sfRectangleShape_setSize(cam, V2F(Editor.camera[0] + Editor.camera[1],
        Editor.camera[2] + Editor.camera[3]));
    sfRectangleShape_setOrigin(cam, V2F(Editor.camera[0], Editor.camera[2]));
    sfRectangleShape_setFillColor(cam, sfTransparent);
    sfRectangleShape_setOutlineColor(cam, RGB(200, 0, 200));
    sfRectangleShape_setOutlineThickness(cam, 2.0f);
    sfRenderWindow_drawRectangleShape(Win.self, cam, NULL);
    sfRectangleShape_destroy(cam);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_trigger_bound(void)
{
    sfRectangleShape *trigger = sfRectangleShape_create();
    v2f_t size = V2F(Editor.trigger[0], Editor.trigger[1]);

    sfRectangleShape_setSize(trigger, size);
    sfRectangleShape_setOrigin(trigger, V2F(size.x / 2.0f, size.y / 2.0f));
    sfRectangleShape_setPosition(trigger, V2F(Editor.trigger[2],
        Editor.trigger[3]));
    sfRectangleShape_setFillColor(trigger, sfTransparent);
    sfRectangleShape_setOutlineColor(trigger, RGB(0, 0, 255));
    sfRectangleShape_setOutlineThickness(trigger, 2.0f);
    sfRenderWindow_drawRectangleShape(Win.self, trigger, NULL);
    sfRectangleShape_destroy(trigger);
}

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
    draw_camera_bound();
    draw_trigger_bound();
    draw_editor_ui();
    Editor.oldMouse = Editor.crtMouse;
}
