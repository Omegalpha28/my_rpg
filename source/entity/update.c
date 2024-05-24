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
static void entity_update(entity_t *evil)
{
    if (evil->actor->damaged)
        return;
    if (evil->attack_types == Boss){
        boss_movement(evil);
        boss_action(evil);
        if (!evil->has_spawn && evil->actor->done){
            evil->movement = Time.currentTime;
            evil->has_spawn = !evil->has_spawn;
        }
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
