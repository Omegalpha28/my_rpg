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
static void set_interactable_texture(interactable_t *obj)
{
    if (obj->type == INTERACTABLE_WEAPON)
        obj->img = Assets.weapons;
}

///////////////////////////////////////////////////////////////////////////////
interactable_t *spawn_interactable(interactable_type_t type, v2f_t position,
    int firstData, void (*interact)(interactable_t *obj))
{
    interactable_t *obj = (interactable_t *)(malloc(sizeof(interactable_t)));

    obj->type = type;
    obj->position = position;
    obj->time = Time.currentTime;
    obj->sprite = sfSprite_create();
    obj->data[0] = firstData;
    obj->interact = interact;
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
    FREE(obj);
}
