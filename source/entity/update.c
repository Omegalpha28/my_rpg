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
}

///////////////////////////////////////////////////////////////////////////////
static void entity_draw(void)
{
    for (uint_t i = 0; i < Entities.count; i++){
        actor_draw(Entities.array[i]->actor);
        health_examination(Entities.array[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
void update_entity(void)
{
    for (uint_t i = 0; i < Entities.count; i++){
        if (Entities.array[i]->dead)
            continue;
        enemy_update(Entities.array[i]);
    }
    entity_draw();
}
