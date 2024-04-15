/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** camera
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void camera_move(void)
{
    v2f_t offset = Player.velocity;
    v2f_t player_pos = MAP_TO_PXF(Player.ref->position);
    v2f_t padding = {75 * Win.width / Win.viewWidth,
        75 * Win.height / Win.viewHeight};

    if (player_pos.x < padding.x ||
        player_pos.y < padding.y ||
        player_pos.x > Win.width - padding.x ||
        player_pos.y > Win.height - padding.y) {
        sfView_move(Win.view, offset);
        sfRenderWindow_setView(Win.self, Win.view);
    }
}

///////////////////////////////////////////////////////////////////////////////
void cursor_focus(void)
{
    v2f_t padding = {30 * Win.width / Win.viewWidth,
        30 * Win.height / Win.viewHeight};
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t offset = {cr.x - (Win.width - padding.x),
        cr.y - (Win.height - padding.y)};

    cr = MAP_TO_PXF(cr);
    if (cr.x < padding.x || cr.y < padding.y ||
        cr.x > Win.width - padding.x || cr.y > Win.height - padding.y) {
        padding = padding;
        sfView_move(Win.view, (v2f_t){0.0f, 0.0f});
        sfRenderWindow_setView(Win.self, Win.view);
    }
}

///////////////////////////////////////////////////////////////////////////////
void draw_debug_safe(void)
{
    sfRectangleShape *cam = sfRectangleShape_create();
    v2f_t center = {Win.width / 2, Win.height / 2};

    sfRectangleShape_setSize(cam, (v2f_t){Win.viewWidth - 150.0f,
        Win.viewHeight - 150.0f});
    sfRectangleShape_setOutlineColor(cam, sfBlue);
    sfRectangleShape_setOutlineThickness(cam, 1.0f);
    sfRectangleShape_setFillColor(cam, sfTransparent);
    sfRectangleShape_setOrigin(cam, (v2f_t){(Win.viewWidth - 150.0f) / 2,
        (Win.viewHeight - 150.0f) / 2});
    sfRectangleShape_setPosition(cam, PX_TO_MAPF(center));
    sfRenderWindow_drawRectangleShape(Win.self, cam, NULL);
    camera_move();
    cursor_focus();
}
//? if player outside safe place; move camera
//? if map ends and if player isnt in safe place move or not ?
//? dash movement
//? collisions in moon/object/actor ?
