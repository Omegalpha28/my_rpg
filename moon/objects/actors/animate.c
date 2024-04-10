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
    sfSprite_setPosition(act->sprite, act->position);
    sfSprite_setRotation(act->sprite, act->rotation);
    sfSprite_setScale(act->sprite, act->scale);
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
    printf("Animate: %u/%u\n", act->frame, anim->frameCount);
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
    actor_update_transform(act);
    sfSprite_setTextureRect(act->sprite, actor_generate_mask(act));
    sh = act->self->sheets[act->sheetId];
    sfSprite_setTexture(act->sprite, act->isVariant ?
        sh->variants[act->variantId]->self : sh->image->self, false);
    sfRenderWindow_drawSprite(Win.self, act->sprite, NULL);
}
