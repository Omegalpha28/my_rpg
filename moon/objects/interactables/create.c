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
static cstring_t CURRENCIES[CURRENCY_COUNT] = {
    "gems",
    "cookies",
    "doraditos_blue",
    "doraditos",
    "eldritch_meat",
    "fish",
    "honeycomb",
    "lettuce",
    "mushroom",
    "salt"
};

///////////////////////////////////////////////////////////////////////////////
static void set_interactable_texture_currency(interactable_t *obj)
{
    obj->data[0] = clamp(obj->data[0], 0, (CURRENCY_COUNT - 1));
    obj->eff = effect(CURRENCIES[obj->data[0]], obj->position, false);
    obj->img = obj->eff->self->self;
    sfSprite_setScale(obj->eff->sprite, V2F1(.8f));
}

///////////////////////////////////////////////////////////////////////////////
static void set_interactable_actor(interactable_t *obj)
{
    if (obj->type == INTERACTABLE_PNJ)
        obj->actor = actor_create(Assets.creatures[CREATURE_PNJ],
            obj->position);
    if (obj->type == INTERACTABLE_CHEST) {
        obj->actor = actor_create(Assets.creatures[CREATURE_CHEST],
            obj->position);
        sfx(SFX_CHEST_FALL);
    }
    if (obj->type == INTERACTABLE_EGG) {
        obj->actor = actor_create(Assets.creatures[CREATURE_PLAYER],
            obj->position);
        actor_set_sheet(obj->actor, "eggs");
        actor_set_variant(obj->actor, NULL, obj->data[0]);
        obj->img = obj->actor->self->sheets[obj->actor->sheetId]->image;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void set_interactable_texture(interactable_t *obj)
{
    obj->img = NULL;
    obj->actor = NULL;
    obj->eff = NULL;
    if (obj->type == INTERACTABLE_WEAPON)
        obj->img = Assets.weapons;
    set_interactable_actor(obj);
    if (obj->type == INTERACTABLE_CHEST || obj->type == INTERACTABLE_PNJ) {
        actor_set_sheet_id(obj->actor, obj->data[0]);
        actor_set_anim(obj->actor, "idle");
        obj->img = obj->actor->self->sheets[obj->actor->sheetId]->image;
    }
    if (obj->type == INTERACTABLE_CURRENCY)
        set_interactable_texture_currency(obj);
}

///////////////////////////////////////////////////////////////////////////////
interactable_t *spawn_interactable(interactable_type_t type, v2f_t position,
    int firstData, void (*interact)(interactable_t *obj))
{
    interactable_t *obj = (interactable_t *)(malloc(sizeof(interactable_t)));

    obj->type = type;
    obj->position = position;
    obj->time = Time.currentTime;
    obj->data[0] = firstData;
    obj->interact = interact;
    obj->sprite = NULL;
    if (type == INTERACTABLE_WEAPON)
        obj->sprite = sfSprite_create();
    for (uint_t i = 1; i < 4; i++)
        obj->data[i] = -1;
    set_interactable_texture(obj);
    Pool.interCount++;
    Pool.inters = REALLOC(Pool.inters, sizeof(interactable_t *),
        Pool.interCount);
    Pool.inters[Pool.interCount - 1] = obj;
    return (obj);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_interactable(interactable_t *obj)
{
    interactable_t **tmp = NULL;
    uint_t j = 0;

    if (obj == NULL)
        return;
    tmp = malloc(sizeof(interactable_t *) * (Pool.interCount - 1));
    for (uint_t i = 0; i < Pool.interCount; i++) {
        if (Pool.inters[i] == obj)
            continue;
        tmp[j] = Pool.inters[i];
        j++;
    }
    Pool.interCount--;
    FREE(Pool.inters);
    Pool.inters = tmp;
    if (obj->sprite != NULL)
        sfSprite_destroy(obj->sprite);
    actor_destroy(obj->actor);
    effect_destroy(obj->eff);
    FREE(obj);
}
