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
static void view_move(v2f_t offset)
{
    offset = normalize2f(offset);
    offset.x *= Time.deltaTime / (DASH ? 12 : 15);
    offset.y *= Time.deltaTime / (DASH ? 12 : 15);
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
    v2f_t offset = {0.0f, 0.0f};

    if (Editor.camera[0] + Editor.camera[1] < DEFAULT_VIEW_WIDTH)
        offset.x = 0.0f;
    if (Editor.camera[2] + Editor.camera[3] < DEFAULT_VIEW_HEIGHT)
        offset.y = 0.0f;
    camera_move();
    view_move(offset);
}
