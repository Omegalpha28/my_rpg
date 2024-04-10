/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** animate
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static void actor_update_transform(actor_t *act)
{
    sheet_t *sh = act->self->sheets[act->sheetId];
    image_t *img = act->isVariant ? sh->variants[act->variantId] : sh->image;

    sfSprite_setPosition(act->sprite, act->position);
    sfSprite_setRotation(act->sprite, act->rotation);
    sfSprite_setScale(act->sprite, act->scale);
    sfSprite_setOrigin(act->sprite, (v2f_t){img->mask.width / 2.0f,
        img->mask.height / 2.0f});
}

///////////////////////////////////////////////////////////////////////////////
static recti_t actor_generate_mask(actor_t *act)
{
    sheet_t *sheet = act->self->sheets[act->sheetId];
    animation_t *anim = sheet->anims[act->animId];
    ulong_t ems = (Time.currentTime - act->time);
    recti_t mask = {0, 0, 0, 0};

    mask = sheet->image->mask;
    act->frame = (uint_t)(((ems / anim->frameRate) % anim->frameCount) +
        anim->startingFrame);
    mask.left = (act->frame % sheet->image->grid.x) * mask.width;
    mask.top = (act->frame / sheet->image->grid.x) * mask.height;
    return (mask);
}

///////////////////////////////////////////////////////////////////////////////
void actor_draw(actor_t *act)
{
    sheet_t *sh = NULL;

    if (act == NULL || act->draw == false || act->self == NULL ||
        act->self->sheetCount == 0)
        return;
    if (act->sheetId >= act->self->sheetCount)
        act->sheetId = 0;
    if (act->animId >= act->self->sheets[act->sheetId]->animCount)
        act->animId = 0;
    sh = act->self->sheets[act->sheetId];
    actor_update_transform(act);
    sfSprite_setTexture(act->sprite, act->isVariant ?
        sh->variants[act->variantId]->self : sh->image->self, false);
    sfSprite_setTextureRect(act->sprite, actor_generate_mask(act));
    sfRenderWindow_drawSprite(Win.self, act->sprite, NULL);
}
