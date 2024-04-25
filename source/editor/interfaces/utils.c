/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** utils
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_rect(v2f_t size, v2f_t pos, sfColor color)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setFillColor(rect, color);
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setScale(rect, FACTORS(size));
    sfRectangleShape_setPosition(rect, PX_TO_MAPF(pos));
    sfRenderWindow_drawRectangleShape(Win.self, rect, NULL);
    sfRectangleShape_destroy(rect);
}

///////////////////////////////////////////////////////////////////////////////
bool_t cursor_inbound(v2f_t position, v2f_t size)
{
    v2i_t cursor = sfMouse_getPositionRenderWindow(Win.self);

    if ((cursor.x >= position.x && cursor.x <= position.x + size.x) &&
        (cursor.y >= position.y && cursor.y <= position.y + size.y))
        return (true);
    return (false);
}
