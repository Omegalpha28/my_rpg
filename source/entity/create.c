/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** create
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void init_entity(entity_t *new, creature_t *creature)
{
    new->actor = actor_create(creature, (v2f_t){0, 0});
    new->health = 10;
    new->has_spawn = 0;
    new->behavior = 0;
    new->last_action = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
entity_t *entity_creation(creature_t *creature)
{
    entity_t *new = (entity_t *)malloc(sizeof(entity_t));

    init_entity(new, creature);

    Entities.count++;
    Entities.array = REALLOC(Entities.array, sizeof(entity_t *), Entities.count);
    Entities.array[Entities.count - 1] = new;
    return (new);

}

///////////////////////////////////////////////////////////////////////////////
void remove_entity(entity_t *ent)
{
    entity_t **tmp = NULL;
    uint_t j = 0;

    if (ent == NULL)
        return;
    if (ent->actor != NULL)
        destroy_actor(ent->actor);
    tmp = malloc(sizeof(entity_t *) * (Entities.count - 1));
    for (uint_t i = 0; i < Entities.count; i++) {
        if (Entities.array[i] == ent)
            continue;
        tmp[j] = Entities.array[i];
        j++;
    }
    Entities.count--;
    FREE(Entities.array);
    Entities.array = tmp;
    FREE(ent);
}


/*
TODO structure containing all information of the creature. aka:
*/