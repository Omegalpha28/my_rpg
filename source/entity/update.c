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
static void enemy_update(entity_t *evil)
{
    if (evil->actor->damaged)
        return;
    enemy_movement(evil);
    enemy_action(evil);
}

///////////////////////////////////////////////////////////////////////////////
void update_entity(void)
{
    for (int i = 0; i < Entities.count; i++){
        health_examination(Entities.array[i]);
        if (Entities.array[i]->actor->dead)
            continue;
        enemy_update(Entities.array[i]);
    }
}
