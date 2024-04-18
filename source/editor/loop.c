/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void add_prop(sheet_t *sheet, prop_t ***array, uint_t *count)
{
    prop_t *prop = prop_create(sheet, (v2f_t){0.0f, 0.0f},
        (v2f_t){1.0f, 1.0f}, 0);

    if (!prop)
        return;
    (*count)++;
    (*array) = REALLOC((*array), sizeof(prop_t *), (*count));
    (*array)[(*count) - 1] = prop;
}

///////////////////////////////////////////////////////////////////////////////
static void draw_hitbox(void)
{
    sfRectangleShape *hitbox;

    if (Editor.focus == NULL)
        return;
    hitbox = sfRectangleShape_create();
    sfRectangleShape_setSize(hitbox, (v2f_t){
        (float)Editor.focus->self->image->mask.width,
        (float)Editor.focus->self->image->mask.height});
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    sfRectangleShape_setOrigin(hitbox, (v2f_t){
        (float)Editor.focus->self->image->mask.width / 2.0f,
        (float)Editor.focus->self->image->mask.height / 2.0f});
    sfRectangleShape_setOutlineColor(hitbox, Editor.dragging ? sfRed : sfBlue);
    sfRectangleShape_setOutlineThickness(hitbox, 1.0f);
    sfRectangleShape_setPosition(hitbox, Editor.focus->position);
    sfRenderWindow_drawRectangleShape(Win.self, hitbox, NULL);
    sfRectangleShape_destroy(hitbox);
}

///////////////////////////////////////////////////////////////////////////////
void editor_loop(void)
{
    sfEvent evt;

    if (Editor.hover == false) {
        add_prop(Assets.zones[0]->categories[0]->sheets[0], &(Editor.fProps),
            &(Editor.fCount));
        add_prop(Assets.zones[0]->categories[5]->sheets[2], &(Editor.fProps),
            &(Editor.fCount));
        Editor.hover = true;
    }
    Editor.crtMouse = sfRenderWindow_mapPixelToCoords(Win.self,
        sfMouse_getPositionRenderWindow(Win.self), Win.view);
    while (sfRenderWindow_pollEvent(Win.self, &evt))
        handle_editor_events(evt);
    for (uint_t i = 0; i < Editor.bCount; i++)
        prop_draw(Editor.bProps[i]);
    for (uint_t i = 0; i < Editor.fCount; i++)
        prop_draw(Editor.fProps[i]);
    draw_hitbox();
    Editor.oldMouse = Editor.crtMouse;
}
