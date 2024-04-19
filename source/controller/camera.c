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

static v2f_t move_in(v2f_t offset, v2f_t center, v2f_t padding)
{
    v2f_t pos = Player.ref->position;

    if (pos.x > center.x + padding.x / 6)
        offset.x = SPEED;
    if (pos.y > center.y + padding.y / 9)
        offset.y = SPEED;
    if (pos.x < center.x - padding.x / 6)
        offset.x = -SPEED;
    if (pos.y < center.y - padding.y / 9)
        offset.y = -SPEED;
    return offset;
}

static void view_move(v2f_t offset)
{
    offset = normalize2f(offset);
    offset.x *= Time.deltaTime / 15;
    offset.y *= Time.deltaTime / 15;
    sfView_move(Win.view, offset);
    sfRenderWindow_setView(Win.self, Win.view);
}

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
    view_move(offset);
}

///////////////////////////////////////////////////////////////////////////////
void cursor_focus(void)
{
    v2f_t padding = {30 * Win.width / Win.viewWidth,
        30 * Win.height / Win.viewHeight};
    v2f_t center = sfView_getCenter(Win.view);
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t mouse = MAP_TO_PXF(cr);
    v2f_t offset = {0.0f, 0.0f};
    v2f_t pos = Player.ref->position;

    if (mouse.x < padding.x && pos.x < center.x + padding.x / 2)
        offset.x = -SPEED;
    if (mouse.y < padding.y && pos.y < center.y + padding.y / 3)
        offset.y = -SPEED;
    if (mouse.x > Win.width - padding.x && pos.x > center.x - padding.x / 2)
        offset.x = SPEED;
    if (mouse.y > Win.height - padding.y && pos.y > center.y - padding.y / 3)
        offset.y = SPEED;
    if (mouse.x > padding.x && mouse.y > padding.y &&
        mouse.x < Win.width - padding.x && mouse.y < Win.height - padding.y)
        offset = move_in(offset, center, padding);
    view_move(offset);
}

///////////////////////////////////////////////////////////////////////////////
void draw_debug_safe(void)
{
    sfRectangleShape *cam = sfRectangleShape_create();
    v2f_t center = {Win.width / 2, Win.height / 2};

    sfRectangleShape_setSize(cam, (v2f_t){Win.viewWidth - 150.0f,
        Win.viewHeight - 150.0f});
    sfRectangleShape_setOutlineColor(cam, sfGreen);
    sfRectangleShape_setOutlineThickness(cam, 1.0f);
    sfRectangleShape_setFillColor(cam, sfTransparent);
    sfRectangleShape_setOrigin(cam, (v2f_t){(Win.viewWidth - 150.0f) / 2,
        (Win.viewHeight - 150.0f) / 2});
    sfRectangleShape_setPosition(cam, PX_TO_MAPF(center));
    sfRenderWindow_drawRectangleShape(Win.self, cam, NULL);
    cursor_focus();
}
