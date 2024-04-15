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
    float padding_x = 75 * Win.width / Win.viewWidth;
    float padding_y = 75 * Win.height / Win.viewHeight;

    if (player_pos.x < padding_x ||
        player_pos.y < padding_y ||
        player_pos.x > Win.width - padding_x ||
        player_pos.y > Win.height - padding_y) {
        sfView_move(Win.view, offset);
        sfRenderWindow_setView(Win.self, Win.view);
    }
}

///////////////////////////////////////////////////////////////////////////////
void draw_debug_safe(void)
{
    sfRectangleShape *cam = sfRectangleShape_create();

    sfRectangleShape_setSize(cam, (v2f_t){Win.viewWidth - 150.0f,
        Win.viewHeight - 150.0f});
    sfRectangleShape_setOutlineColor(cam, sfBlue);
    sfRectangleShape_setOutlineThickness(cam, 1.0f);
    sfRectangleShape_setFillColor(cam, sfTransparent);
    sfRectangleShape_setOrigin(cam, (v2f_t){(Win.viewWidth - 150.0f) / 2,
        (Win.viewHeight - 150.0f) / 2});
    sfRectangleShape_setPosition(cam, (v2f_t){0.0f, 0.0f});
    sfRenderWindow_drawRectangleShape(Win.self, cam, NULL);
    camera_move();
}
//? if player outside safe place; move camera
//? if map ends and if player isnt in safe place move or not ?
//? dash movement
//? collisions in moon/object/actor ?
