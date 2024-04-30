/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** draw
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static recti_t prop_generate_mask(prop_t *prop)
{
    sheet_t *sheet = prop->self;
    animation_t *anim = sheet->animCount ? sheet->anims[0] : NULL;
    ulong_t ems = (Time.currentTime - prop->time);
    recti_t mask = sheet->image->mask;

    if (sheet->animCount == 0 || !prop->animated)
        return (prop->done ? (recti_t){anim->endingFrame %
            sheet->image->grid.x * mask.width, anim->endingFrame /
            sheet->image->grid.x * mask.height, mask.width, mask.height} :
            sheet->image->mask);
    prop->frame = (uint_t)(((ems / DEFAULT_PROP_FR) % anim->frameCount) +
        anim->startingFrame);
    mask.left = (prop->frame % sheet->image->grid.x) * mask.width;
    mask.top = (prop->frame / sheet->image->grid.x) * mask.height;
    if (prop->once && prop->frame == prop->self->anims[0]->endingFrame) {
        prop->animated = false;
        prop->done = true;
    }
    return (mask);
}

///////////////////////////////////////////////////////////////////////////////
recti_t prop_generate_fixed_mask(prop_t *prop)
{
    sheet_t *sheet = prop->self;
    recti_t mask = sheet->image->mask;

    mask.left = (prop->frame % sheet->image->grid.x) * mask.width;
    mask.top = (prop->frame / sheet->image->grid.x) * mask.height;
    return (mask);
}

///////////////////////////////////////////////////////////////////////////////
void prop_draw(prop_t *prop)
{
    recti_t mask = {0, 0, 0, 0};

    if (prop == NULL || prop->sprite == NULL || prop->draw == false ||
        prop->self == NULL || prop->self->image == NULL ||
        prop->self->image->self == NULL)
        return;
    sfSprite_setTexture(prop->sprite, prop->self->image->self, false);
    mask = (prop->data[0] == 1) ? prop_generate_fixed_mask(prop) :
        prop_generate_mask(prop);
    sfSprite_setTextureRect(prop->sprite, mask);
    sfSprite_setOrigin(prop->sprite, (v2f_t){mask.width / 2.0f,
        mask.height / 2.0f});
    sfRenderWindow_drawSprite(Win.self, prop->sprite, NULL);
}

///////////////////////////////////////////////////////////////////////////////
void prop_animate(prop_t *prop)
{
    if (!prop || !prop->self || !prop->self->image || !prop->self->image->self
        || prop->once == false)
        return;
    prop->time = Time.currentTime;
    prop->done = false;
    prop->animated = true;
}

///////////////////////////////////////////////////////////////////////////////
void draw_visible_props(prop_t **list, uint_t n)
{
    v2f_t ctr = sfView_getCenter(Win.view);
    rectf_t vBound = {ctr.x - Win.viewWidth / 2.0f, ctr.y - Win.viewHeight /
        2.0f, Win.viewWidth, Win.viewHeight};
    rectf_t bound = {0.0f, 0.0f, 0.0f, 0.0f};

    for (uint_t i = 0; i < n; i++) {
        bound.width = list[i]->self->image->mask.width;
        bound.height = list[i]->self->image->mask.height;
        bound.left = list[i]->position.x - (bound.width / 2.0f);
        bound.top = list[i]->position.y - (bound.height / 2.0f);
        if (sfFloatRect_intersects(&bound, &vBound, NULL))
            prop_draw(list[i]);
    }
}
