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
    if (!anim->looped && act->frame == anim->endingFrame)
        act->done = true;
    return (mask);
}

///////////////////////////////////////////////////////////////////////////////
static void boss_draw_shadow(actor_t *act)
{
    sfSprite *shadow = sfSprite_create();

    sfSprite_setTexture(shadow, Assets.ui[UI_SHADOW_BOSS]->self, false);
    sfSprite_setOrigin(shadow, V2F(48.5f, 19.0f));
    sfSprite_setPosition(shadow, add2f(act->position, V2F(act->scale.x < 0.0f ?
        1.0f : 0.0f, act->self->sheets[act->sheetId]->image->mask.height /
        2.0f)));
    sfSprite_setColor(shadow, RGBA(255, 255, 255, 150));
    sfRenderWindow_drawSprite(Win.self, shadow, NULL);
    sfSprite_destroy(shadow);
}

///////////////////////////////////////////////////////////////////////////////
static void actor_draw_shadow(actor_t *act)
{
    recti_t mask = {32, 4, 20, 5};
    recti_t tMask = act->self->sheets[act->sheetId]->image->mask;
    sfSprite *shadow = sfSprite_create();
    float scale = tMask.width / mask.width;

    sfSprite_setTexture(shadow, Assets.ui[PLAYER_SHADOW]->self, false);
    sfSprite_setTextureRect(shadow, mask);
    sfSprite_setOrigin(shadow, V2F(mask.width / 2.0f, mask.height / 2.0f));
    sfSprite_setScale(shadow, V2F1(scale));
    sfSprite_setPosition(shadow, add2f(act->position, V2F(act->scale.x < 0.0f ?
        1.0f : 0.0f, act->self->sheets[act->sheetId]->image->mask.height /
        2.0f)));
    sfSprite_setColor(shadow, RGBA(255, 255, 255, 150));
    sfRenderWindow_drawSprite(Win.self, shadow, NULL);
    sfSprite_destroy(shadow);
}

///////////////////////////////////////////////////////////////////////////////
static void cast_shadow(actor_t *act)
{
    if (act->castShadow == false)
        return;
    if (act->self->id == CREATURE_CRAB_BOSS)
        boss_draw_shadow(act);
    else
        actor_draw_shadow(act);
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
    cast_shadow(act);
    sfRenderWindow_drawSprite(Win.self, act->sprite, NULL);
}
