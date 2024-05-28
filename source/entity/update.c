/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_entitiy
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
static void intro(entity_t *boss)
{
    if (boss->has_spawn)
        return;
    boss->actor->castShadow = false;
    actor_set_sheet(boss->actor, "intro");
    if (boss->actor->done){
        boss->movement = Time.currentTime;
        boss->has_spawn = !boss->has_spawn;
        boss->actor->castShadow = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void entity_update(entity_t *evil)
{
    if (evil->actor->damaged)
        return;
    if (evil->attack_types == Boss){
        intro(evil);
        if (!evil->has_spawn)
            return;
        boss_movement(evil);
        boss_action(evil);
    } else {
        enemy_movement(evil);
        enemy_action(evil);
    }
}

///////////////////////////////////////////////////////////////////////////////
void update_entity(void)
{
    for (int i = 0; i < Entities.count; i++){
        health_examination(Entities.array[i]);
        if (Entities.array[i]->actor->dead)
            continue;
        entity_update(Entities.array[i]);
    }
}
