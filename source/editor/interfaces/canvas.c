/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** canvas
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_editor_map_border(void)
{
    sfRectangleShape *border = sfRectangleShape_create();

    sfRectangleShape_setSize(border, V2F1(65536.0f * 2.0f));
    sfRectangleShape_setOrigin(border, V2F1(65536.0f));
    sfRectangleShape_setFillColor(border, sfWhite);
    sfRenderWindow_drawRectangleShape(Win.self, border, NULL);
    sfRectangleShape_destroy(border);
}

///////////////////////////////////////////////////////////////////////////////
void draw_editor_focus_hitbox(void)
{
    sfRectangleShape *hitbox;

    if (Editor.focus == NULL)
        return;
    hitbox = sfRectangleShape_create();
    sfRectangleShape_setSize(hitbox, (v2f_t){
        (float)Editor.focus->self->image->mask.width - 2.0f,
        (float)Editor.focus->self->image->mask.height - 2.0f});
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    sfRectangleShape_setOrigin(hitbox, (v2f_t){
        (float)Editor.focus->self->image->mask.width / 2.0f - 1.0f,
        (float)Editor.focus->self->image->mask.height / 2.0f - 1.0f});
    sfRectangleShape_setOutlineColor(hitbox, Editor.dragging ?
        sfColor_fromRGBA(255, 0, 0, 155) : sfColor_fromRGBA(0, 0, 255, 155));
    sfRectangleShape_setOutlineThickness(hitbox, 1.0f);
    sfRectangleShape_setPosition(hitbox, Editor.focus->position);
    sfRenderWindow_drawRectangleShape(Win.self, hitbox, NULL);
    sfRectangleShape_destroy(hitbox);
}
