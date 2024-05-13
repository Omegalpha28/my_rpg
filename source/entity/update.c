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
    if (evil->is_dammaged)
        return;
    enemy_movement(evil);
    enemy_action(evil);
}

///////////////////////////////////////////////////////////////////////////////
void update_entity(void)
{
    for (int i = 0; i < Entities.count; i++){
        health_examination(Entities.array[i]);
        if (Entities.array[i]->dead)
            continue;
        enemy_update(Entities.array[i]);
    }
}
