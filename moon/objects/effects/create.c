/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** create
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
effect_t *effect_create(vfx_t *source, v2f_t position)
{
    effect_t *eff = NULL;

    if (source == NULL)
        return (NULL);
    eff = (effect_t *)malloc(sizeof(effect_t));
    eff->frame = 0;
    eff->self = source;
    eff->position = position;
    eff->time = Time.currentTime;
    eff->sprite = sfSprite_create();
    sfSprite_setPosition(eff->sprite, eff->position);
    sfSprite_setOrigin(eff->sprite, (v2f_t){
        eff->self->self->mask.width / 2.0f,
        eff->self->self->mask.height / 2.0f});
    sfSprite_setTexture(eff->sprite, eff->self->self->self, false);
    Pool.effectCount++;
    Pool.effects = REALLOC(Pool.effects, sizeof(effect_t *), Pool.effectCount);
    Pool.effects[Pool.effectCount - 1] = eff;
    return (eff);
}

///////////////////////////////////////////////////////////////////////////////
void effect_destroy(effect_t *eff)
{
    effect_t **tmp = NULL;
    uint_t j = 0;

    if (eff == NULL)
        return;
    tmp = malloc(sizeof(effect_t *) * (Pool.effectCount - 1));
    for (uint_t i = 0; i < Pool.effectCount; i++) {
        if (Pool.effects[i] == eff)
            continue;
        tmp[j] = Pool.effects[i];
        j++;
    }
    Pool.effectCount--;
    FREE(Pool.effects);
    Pool.effects = tmp;
    if (eff->sprite != NULL)
        sfSprite_destroy(eff->sprite);
    FREE(eff);
}

///////////////////////////////////////////////////////////////////////////////
effect_t *effect(cstring_t name, v2f_t position)
{
    for (uint_t i = 0; i < Assets.vfxCount; i++)
        if (CMP(Assets.vfx[i]->name, name))
            return (effect_create(Assets.vfx[i], position));
    return (NULL);
}
