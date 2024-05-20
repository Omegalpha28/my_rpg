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

static void init_entity_stat_block(entity_t *new, creature_t *creature,
    v2f_t position)
{
    new->actor->health = CREATURE_COUNT < creature->id ? 100 :
        Stats[creature->id].health;
    new->speed = CREATURE_COUNT < creature->id ? 0.6 :
        Stats[creature->id].speed;
    new->attack_radius = CREATURE_COUNT < creature->id ? 50 :
        Stats[creature->id].attack_radius;
    new->insight = CREATURE_COUNT < creature->id ? 100 :
        Stats[creature->id].insight;
    new->attack_types = CREATURE_COUNT < creature->id ? 1 :
        Stats[creature->id].attack_types;
    new->dizzy = CREATURE_COUNT < creature->id ? 0 :
        Stats[creature->id].dizzy;
    new->wanted_position = position;
    new->collision = (float)(creature->sheets[new->actor->sheetId]->
        image->mask.height) / 2;
}

///////////////////////////////////////////////////////////////////////////////
static void init_entity(entity_t *new, creature_t *creature, v2f_t position)
{
    new->actor = actor_create(creature, position);
    init_entity_stat_block(new, creature, position);
    new->last_action = 0;
    new->has_spawn = 0;
    new->is_attack = 0;
    new->status = Patrol;
    new->can_attack = true;
    new->cooldown = 5000;
    new->attack_started = false;
    new->movement = 0;
    new->weapon = Stats[creature->id].weapon;
}

///////////////////////////////////////////////////////////////////////////////
entity_t *entity_create(creature_t *creature, v2f_t position)
{
    entity_t *new = (entity_t *)malloc(sizeof(entity_t));

    Entities.count++;
    Entities.array = REALLOC(Entities.array, sizeof(entity_t *),
        Entities.count);
    Entities.array[Entities.count - 1] = new;
    init_entity(new, creature, position);
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
        actor_destroy(ent->actor);
    tmp = malloc(sizeof(entity_t *) * (Entities.count - 1));
    for (int i = 0; i < Entities.count; i++) {
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
