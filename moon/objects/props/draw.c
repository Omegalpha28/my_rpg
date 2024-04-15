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

    if (sheet->animCount == 0 || !sheet->anims[0]->looped)
        return (prop->done ? (recti_t){anim->endingFrame %
            sheet->image->grid.x * mask.width, anim->endingFrame /
            sheet->image->grid.x * mask.height, mask.width, mask.height} :
            sheet->image->mask);
    prop->frame = (uint_t)(((ems / DEFAULT_PROP_FR) % anim->frameCount) +
        anim->startingFrame);
    mask.left = (prop->frame % sheet->image->grid.x) * mask.width;
    mask.top = (prop->frame / sheet->image->grid.x) * mask.height;
    if (prop->once && prop->frame == prop->self->anims[0]->endingFrame) {
        prop->self->anims[0]->looped = false;
        prop->done = true;
    }
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
    mask = prop_generate_mask(prop);
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
    prop->self->anims[0]->looped = true;
}
