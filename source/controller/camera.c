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

static v2f_t move_from_cursor(v2f_t cursor, v2f_t padding)
{
    v2f_t offset = {0.0f, 0.0f};

    if (cursor.x < padding.x)
        offset.x = -SPEED / 2;
    if (cursor.y < padding.y)
        offset.y = -SPEED / 2;
    if (cursor.x > Win.width - padding.x)
        offset.x = SPEED / 2;
    if (cursor.y > Win.height - padding.y)
        offset.y = SPEED / 2;
    offset = normalize2f(offset);
    return offset;
}

static v2f_t move_from_player(v2f_t cursor, v2f_t padding)
{
    v2f_t offset = {0.0f, 0.0f};
    v2f_t marge = {padding.x * 3, padding.y * 3};

    if (cursor.x > padding.x && cursor.x < marge.x)
        offset.x = SPEED / 2;
    if (cursor.y > padding.y && cursor.y < marge.y)
        offset.y = SPEED / 2;
    if (cursor.x < Win.width - padding.x && cursor.x > Win.width - marge.x)
        offset.x = -SPEED / 2;
    if (cursor.y < Win.height - padding.y && cursor.y > Win.height - marge.y)
        offset.y = -SPEED / 2;
    offset = normalize2f(offset);
    return offset;
}

///////////////////////////////////////////////////////////////////////////////
void cursor_focus(void)
{
    v2f_t padding = {30 * Win.width / Win.viewWidth,
        30 * Win.height / Win.viewHeight};
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t mouse = MAP_TO_PXF(cr);
    v2f_t max_zoom = {Win.viewWidth * 1.10, Win.viewHeight * 1.10};
    v2f_t size = sfView_getSize(Win.view);

    if (mouse.x < padding.x || mouse.y < padding.y ||
        mouse.x > Win.width - padding.x || mouse.y > Win.height - padding.y) {
        if (size.x < max_zoom.x && size.y < max_zoom.y) {
            sfView_move(Win.view, move_from_cursor(mouse, padding));
            sfView_zoom(Win.view, 1.005f);
        }
    } else
        if (size.x > Win.viewWidth && size.y > Win.viewHeight) {
            sfView_move(Win.view, move_from_player(mouse, padding));
            sfView_zoom(Win.view, 0.995f);
        }
    sfRenderWindow_setView(Win.self, Win.view);
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
