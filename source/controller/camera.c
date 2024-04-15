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
static void draw_debug_safe(void)
{
    sfRectangleShape *cam = sfRectangleShape_create();

    sfRectangleShape_setSize(cam, (v2f_t){Win.viewWidth - 100.0f,
        Win.viewHeight - 100.0f});
    sfRectangleShape_setOutlineColor(cam, sfBlue);
    sfRectangleShape_setOutlineThickness(cam, 1.0f);
    sfRectangleShape_setFillColor(cam, sfTransparent);
    sfRectangleShape_setOrigin(cam, (v2f_t){(Win.viewWidth - 100.0f) / 2,
        (Win.viewHeight - 100.0f) / 2});
    sfRectangleShape_setPosition(cam, (v2f_t){0.0f, 0.0f});
    sfRenderWindow_drawRectangleShape(Win.self, cam, NULL);
}
//? if player outside safe place; move camera
//? if map ends and if player isnt in safe place move or not ?
//? dash movement
//? collisions in moon/object/actor ?
