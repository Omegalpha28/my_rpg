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
static void mob_update(entity_t *evil)
{
    if (evil->actor->damaged)
        return;
    enemy_movement(evil);
    enemy_action(evil);
}

///////////////////////////////////////////////////////////////////////////////
static void boss_update(boss_t *evil)
{
    if (evil->actor->damaged)
        return;
    boss_movement(evil);
    boss_action(evil);
}

///////////////////////////////////////////////////////////////////////////////
void update_entity(void)
{
    for (int i = 0; i < Entities.count; i++){
        health_examination(Entities.array[i]);
        if (Entities.array[i]->actor->dead)
            continue;
        mob_update(Entities.array[i]);
    }
    for (int i = 0; i < Entities.bcount; i++){
        if (Entities.boss_array[i]->actor->dead)
            continue;
        boss_update(Entities.boss_array[i]);
    }
}
