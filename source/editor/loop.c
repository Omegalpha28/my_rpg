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
void remove_prop(prop_t *prop, prop_t ***array, uint_t *count)
{
    prop_t **tmp = NULL;
    uint_t j = 0;
    bool_t found = false;

    for (uint_t i = 0; prop && i < (*count); i++)
        found = (*array)[i] == prop ? true : found;
    if (!found)
        return;
    tmp = malloc(sizeof(prop_t *) * ((*count) - 1));
    for (uint_t i = 0; i < (*count); i++) {
        if ((*array)[i] == prop)
            continue;
        tmp[j] = (*array)[i];
        j++;
    }
    (*count)--;
    FREE((*array));
    (*array) = tmp;
    prop_destroy(prop);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_hitbox(void)
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

///////////////////////////////////////////////////////////////////////////////
static void draw_ui(void)
{
    sfRectangleShape *container = sfRectangleShape_create();
    v2f_t size = {175, 320};

    sfRectangleShape_setFillColor(container, sfColor_fromRGB(100, 100, 100));
    sfRectangleShape_setSize(container, size);
    sfRectangleShape_setScale(container, FACTORS(size));
    sfRectangleShape_setPosition(container, PX_TO_MAPF(((v2f_t){10, 25})));
    sfRenderWindow_drawRectangleShape(Win.self, container, NULL);
    sfRectangleShape_destroy(container);
}

///////////////////////////////////////////////////////////////////////////////
void editor_loop(void)
{
    sfEvent evt;

    Editor.crtMouse = sfRenderWindow_mapPixelToCoords(Win.self,
        sfMouse_getPositionRenderWindow(Win.self), Win.view);
    while (sfRenderWindow_pollEvent(Win.self, &evt))
        handle_editor_events(evt);
    for (uint_t i = 0; Editor.bDisplay && i < Editor.bCount; i++)
        prop_draw(Editor.bProps[i]);
    actor_draw(Player.ref);
    for (uint_t i = 0; Editor.fDisplay && i < Editor.fCount; i++)
        prop_draw(Editor.fProps[i]);
    draw_hitbox();
    draw_ui();
    Editor.oldMouse = Editor.crtMouse;
}
