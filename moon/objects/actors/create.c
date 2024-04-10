/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** create
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static void actor_init(actor_t *act, creatures_t *creature, v2f_t position)
{
    act->animId = 0;
    act->variantId = 0;
    act->sheetId = 0;
    act->frame = 0;
    act->isVariant = false;
    act->time = Time.currentTime;
    act->position = position;
    act->rotation = 0.0f;
    act->scale = (v2f_t){1.0f, 1.0f};
    act->sprite = sfSprite_create();
    act->self = creature;
    sfSprite_setPosition(act->sprite, position);
    act->draw = true;
}

///////////////////////////////////////////////////////////////////////////////
actor_t *actor_create(creatures_t *creature, v2f_t position)
{
    actor_t *act = (actor_t *)malloc(sizeof(actor_t));

    if (act == NULL)
        return (NULL);
    actor_init(act, creature, position);
    Pool.actorCount++;
    Pool.actors = REALLOC(Pool.actors, sizeof(actor_t *), Pool.actorCount);
    Pool.actors[Pool.actorCount - 1] = act;
    return (act);
}

///////////////////////////////////////////////////////////////////////////////
void actor_destroy(actor_t *act)
{
    actor_t **tmp = NULL;
    uint_t j = 0;

    if (act == NULL)
        return;
    if (act->sprite != NULL)
        sfSprite_destroy(act->sprite);
    tmp = malloc(sizeof(actor_t *) * (Pool.actorCount - 1));
    for (uint_t i = 0; i < Pool.actorCount; i++) {
        if (Pool.actors[i] == act)
            continue;
        tmp[j] = Pool.actors[i];
        j++;
    }
    Pool.actorCount--;
    FREE(Pool.actors);
    Pool.actors = tmp;
    FREE(act);
}
