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
static void init_entity_stat_block(entity_t *new, creature_t *creature)
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
    new->firerate = CREATURE_COUNT < creature->id ? 1000 :
        Stats[creature->id].firerate;
    new->ball_count = CREATURE_COUNT < creature->id ? 1 :
        Stats[creature->id].ball_count;
    new->collision = (float)(creature->sheets[new->actor->sheetId]->
        image->mask.height) / 2;
}

///////////////////////////////////////////////////////////////////////////////
static void init_boss_stat_block(entity_t *new, creature_t *creature)
{
    if (new->attack_types == Boss)
        new->attack_amount = CREATURE_COUNT < creature->id ? 3 :
            B_Stats[new->bstat_pos].attack_amount;
    else
        new->attack_amount = 0;
    for (int i = 0; i < MAX_ATTACK; i++)
        new->attack_list[i] = 0;
    for (int i = 0; i < new->attack_amount; i++)
        new->attack_list[i] = CREATURE_COUNT < creature->id ? 1 :
            B_Stats[new->bstat_pos].attack_list[i];
}

///////////////////////////////////////////////////////////////////////////////
static void init_entity(entity_t *new, creature_t *creature, v2f_t position)
{
    new->actor = actor_create(creature, position);
    init_entity_stat_block(new, creature);
    init_boss_stat_block(new, creature);
    new->last_action = 0;
    new->has_spawn = 0;
    new->is_attack = 0;
    new->status = Patrol;
    new->can_attack = true;
    new->cooldown = 5000;
    new->attack_started = false;
    new->movement = 0;
    new->weapon = Stats[creature->id].weapon;
    new->wanted_position = position;
    new->curr_phase = 0;
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
