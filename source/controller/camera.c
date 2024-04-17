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
    v2f_t offset = {0.0f, 0.0f};
    v2f_t player_pos = MAP_TO_PXF(Player.ref->position);
    v2f_t padding = {75 * Win.width / Win.viewWidth,
        75 * Win.height / Win.viewHeight};

    if (player_pos.x < padding.x)
        offset.x = -SPEED;
    if (player_pos.y < padding.y)
        offset.y = -SPEED;
    if (player_pos.x > Win.width - padding.x)
        offset.x = SPEED;
    if (player_pos.y > Win.height - padding.y)
        offset.y = SPEED;
    offset = normalize2f(offset);
    offset.x *= Time.deltaTime / 15;
    offset.y *= Time.deltaTime / 15;
    sfView_move(Win.view, offset);
    sfRenderWindow_setView(Win.self, Win.view);
}

///////////////////////////////////////////////////////////////////////////////
void cursor_focus(void)
{
    v2f_t padding = {30 * Win.width / Win.viewWidth,
        30 * Win.height / Win.viewHeight};
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t mouse = MAP_TO_PXF(cr);
    v2f_t offset = {0.0f, 0.0f};

    padding = padding;
    mouse = mouse;
    sfView_move(Win.view, offset);
    sfRenderWindow_setView(Win.self, Win.view);
}

///////////////////////////////////////////////////////////////////////////////
void draw_debug_safe(void)
{
    sfRectangleShape *cam = sfRectangleShape_create();
    v2f_t center = {Win.width / 2, Win.height / 2};
    sfRectangleShape *r = sfRectangleShape_create();

    sfRectangleShape_setSize(r, (v2f_t){20, 20});
    sfRectangleShape_setOrigin(r, (v2f_t){10, 10});
    sfRectangleShape_setPosition(r, (v2f_t){0, 0});
    sfRectangleShape_setFillColor(r, sfCyan);
    sfRenderWindow_drawRectangleShape(Win.self, r, NULL);
    sfRectangleShape_destroy(r);
    sfRectangleShape_setSize(cam, (v2f_t){Win.viewWidth - 150.0f,
        Win.viewHeight - 150.0f});
    sfRectangleShape_setOutlineColor(cam, sfBlue);
    sfRectangleShape_setOutlineThickness(cam, 1.0f);
    sfRectangleShape_setFillColor(cam, sfTransparent);
    sfRectangleShape_setOrigin(cam, (v2f_t){(Win.viewWidth - 150.0f) / 2,
        (Win.viewHeight - 150.0f) / 2});
    sfRectangleShape_setPosition(cam, PX_TO_MAPF(center));
    sfRenderWindow_drawRectangleShape(Win.self, cam, NULL);
    cursor_focus();
}
