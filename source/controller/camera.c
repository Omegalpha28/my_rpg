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
float ease_in_out_circle(float t)
{
    if (t < 0.5f)
        return (1 - sqrt(1 - 2 * t)) * 0.5f;
    else
        return (1 + sqrt(2 * t - 1)) * 0.5f;
}

///////////////////////////////////////////////////////////////////////////////
v2f_t cursor_cap(void)
{
    v2f_t max_cam = {0.0f, 0.0f};
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t pos = Player.ref->position;
    v2f_t dist = {mouse.x - pos.x, mouse.y - pos.y};

    max_cam.x = ease_in_out_circle(dist.x);
    max_cam.y = ease_in_out_circle(dist.y);
    return (max_cam);
}

///////////////////////////////////////////////////////////////////////////////
void cursor_focus(void)
{
    v2f_t cap = cursor_cap();
    v2f_t pos = Player.ref->position;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t offset = {0.0f, 0.0f};
    v2f_t dist = {mouse.x - pos.x, mouse.y - pos.y};

    if (dist.x > cap.x * 20 && dist.x < cap.x * 30)
        offset.x = cap.x;
    if (dist.y > cap.y * 20 && dist.y < cap.y * 30)
        offset.y = cap.y;
    if (dist.x < cap.x * 20 && dist.x > cap.x * 30)
        offset.x = cap.x;
    if (dist.y < cap.y * 20 && dist.y > cap.y * 30)
        offset.y = cap.y;
    view_move(offset);
}
