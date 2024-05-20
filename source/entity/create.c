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

///////////////////////////////////////////////////////////////////////////////
static void init_boss_stat_block(boss_t *new, creature_t *creature)
{
    new->actor->health = CREATURE_COUNT < creature->id ? 100 :
        B_Stats[new->bstat_position].health;
    new->speed = CREATURE_COUNT < creature->id ? 5 :
        B_Stats[new->bstat_position].speed;
    new->attack_amount = CREATURE_COUNT < creature->id ? 3 :
        B_Stats[new->bstat_position].attack_amount;
    new->dizzy = CREATURE_COUNT < creature->id ? 0 :
        B_Stats[new->bstat_position].dizzy;
    for (int i = 0; i < new->attack_amount; i++)
        new->attack_list[i] = CREATURE_COUNT < creature->id ? 1 :
            B_Stats[new->bstat_position].attack_list[i];
}

///////////////////////////////////////////////////////////////////////////////
static void init_boss(boss_t *new, creature_t *creature, v2f_t position)
{
    new->actor = actor_create(creature, position);
    if (new->actor->self->id == CREATURE_CRAB_BOSS)
        new->bstat_position = 0;
    init_boss_stat_block(new, creature);
    new->can_attack = 0;
    new->cooldown = 0;
    new->is_attack = 0;
    new->movement = 0;
    new->last_action = 0;
    new->curr_phase = 0;
}

///////////////////////////////////////////////////////////////////////////////
boss_t *boss_create(creature_t *creature, v2f_t position)
{
    boss_t *new = (boss_t *)malloc(sizeof(boss_t));

    Entities.bcount++;
    Entities.boss_array = REALLOC(Entities.boss_array, sizeof(boss_t *),
        Entities.bcount);
    Entities.boss_array[Entities.bcount - 1] = new;
    init_boss(new, creature, position);
    return (new);
}

///////////////////////////////////////////////////////////////////////////////
void remove_boss(boss_t *ent)
{
    boss_t **tmp = NULL;
    uint_t j = 0;

    if (ent == NULL)
        return;
    if (ent->actor != NULL)
        actor_destroy(ent->actor);
    tmp = malloc(sizeof(boss_t *) * (Entities.bcount - 1));
    for (int i = 0; i < Entities.count; i++) {
        if (Entities.boss_array[i] == ent)
            continue;
        tmp[j] = Entities.boss_array[i];
        j++;
    }
    Entities.bcount--;
    FREE(Entities.boss_array);
    Entities.boss_array = tmp;
    FREE(ent);
}
