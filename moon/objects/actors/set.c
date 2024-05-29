/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** set
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_anim(actor_t *act, cstring_t name)
{
    sheet_t *sheet;

    if (act == NULL || act->self == NULL || act->self->sheetCount == 0)
        return (false);
    sheet = act->self->sheets[act->sheetId];
    for (uint_t i = 0; i < sheet->animCount; i++) {
        if (!CMP(sheet->anims[i]->name, name))
            continue;
        if (act->animId == i)
            return (true);
        act->animId = i;
        act->time = Time.currentTime;
        act->done = false;
        return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_anim_id(actor_t *act, uint_t id)
{
    sheet_t *sheet;

    if (act == NULL || act->self == NULL || act->self->sheetCount == 0)
        return (false);
    sheet = act->self->sheets[act->sheetId];
    if (id >= sheet->animCount)
        return (false);
    if (act->animId == id)
        return (true);
    act->time = Time.currentTime;
    act->animId = id;
    act->done = false;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_sheet(actor_t *act, cstring_t name)
{
    creature_t *crt;

    if (act == NULL || act->self == NULL)
        return (false);
    crt = act->self;
    for (uint_t i = 0; i < crt->sheetCount; i++) {
        if (!CMP(crt->sheets[i]->name, name))
            continue;
        if (act->sheetId == i)
            return (true);
        act->done = false;
        act->sheetId = i;
        act->time = Time.currentTime;
        if (Engine.debugMode == true)
            actor_set_variant(act, "debug", 0);
        return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_sheet_id(actor_t *act, uint_t id)
{
    creature_t *crt;

    if (act == NULL || act->self == NULL)
        return (false);
    crt = act->self;
    if (id >= crt->sheetCount)
        return (false);
    act->time = Time.currentTime;
    act->sheetId = id;
    if (Engine.debugMode == true)
        actor_set_variant(act, "debug", 0);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_variant(actor_t *act, cstring_t name, uint_t id)
{
    sheet_t *sheet;

    if (act == NULL || act->self == NULL || act->self->sheetCount == 0)
        return (false);
    sheet = act->self->sheets[act->sheetId];
    for (uint_t i = 0; name != NULL && i < sheet->variantCount; i++) {
        if (!CMP(sheet->variants[i]->name, name))
            continue;
        act->isVariant = true;
        act->variantId = i;
        act->time = Time.currentTime;
        return (true);
    }
    if (name == NULL && id < sheet->variantCount) {
        act->isVariant = true;
        act->variantId = id;
        act->time = Time.currentTime;
        return (true);
    }
    return (false);
}
