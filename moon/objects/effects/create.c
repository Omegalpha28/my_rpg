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
static void add_default_effect(effect_t *eff)
{
    eff->frame = 0;
    eff->framerate = DEFAULT_VFX_FR;
    eff->fixFrame = false;
    Pool.effectCount++;
    Pool.effects = REALLOC(Pool.effects, sizeof(effect_t *), Pool.effectCount);
    Pool.effects[Pool.effectCount - 1] = eff;
}

///////////////////////////////////////////////////////////////////////////////
effect_t *effect_create(vfx_t *source, v2f_t position, bool_t isDecal)
{
    effect_t *eff = NULL;

    if (source == NULL)
        return (NULL);
    eff = (effect_t *)malloc(sizeof(effect_t));
    eff->self = source;
    eff->position = position;
    eff->time = Time.currentTime;
    eff->isDecal = isDecal;
    eff->sprite = sfSprite_create();
    sfSprite_setPosition(eff->sprite, eff->position);
    sfSprite_setOrigin(eff->sprite, (v2f_t){
        eff->self->self->mask.width / 2.0f,
        eff->self->self->mask.height / 2.0f});
    sfSprite_setTexture(eff->sprite, eff->self->self->self, false);
    add_default_effect(eff);
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
effect_t *effect(cstring_t name, v2f_t position, bool_t isDecal)
{
    for (uint_t i = 0; i < Assets.vfxCount; i++)
        if (CMP(Assets.vfx[i]->name, name))
            return (effect_create(Assets.vfx[i], position, isDecal));
    return (NULL);
}
