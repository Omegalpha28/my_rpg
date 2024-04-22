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
static recti_t effect_generate_mask(effect_t *eff, bool_t *destroy)
{
    image_t *img = eff->self->self;
    ulong_t ems = (Time.currentTime - eff->time);
    recti_t mask = img->mask;
    uint_t frameCount = eff->self->endingFrame - eff->self->startingFrame + 1;

    mask = img->mask;
    eff->frame = (uint_t)(((ems / DEFAULT_VFX_FR) % frameCount) +
        eff->self->startingFrame);
    mask.left = (eff->frame % img->grid.x) * mask.width;
    mask.top = (eff->frame / img->grid.x) * mask.height;
    if (!eff->self->looped && eff->frame == eff->self->endingFrame)
        *destroy = true;
    return (mask);
}

///////////////////////////////////////////////////////////////////////////////
void effect_draw(effect_t *eff)
{
    bool_t destroy = false;

    if (!eff || !eff->self || !eff->self->self || !eff->self->self->self)
        return;
    if (eff->frame > eff->self->endingFrame && !eff->self->looped)
        return (effect_destroy(eff));
    sfSprite_setTextureRect(eff->sprite, effect_generate_mask(eff, &destroy));
    sfRenderWindow_drawSprite(Win.self, eff->sprite, NULL);
    if (destroy)
        effect_destroy(eff);
}
