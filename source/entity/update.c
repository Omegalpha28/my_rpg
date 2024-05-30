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
static void update_vfx(entity_t *boss)
{
    for (uint_t i = 0; i < Pool.effectCount; i++){
        if (CMP(Pool.effects[i]->self->name, "crab_blood")){
            sfSprite_setPosition(Pool.effects[i]->sprite,
                add2f(boss->actor->position, (v2f_t){0.0f, 10.0f}));
            return;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
static void intro(entity_t *boss)
{
    if (boss->has_spawn)
        return;
    boss->actor->castShadow = false;
    boss->actor->invincible = true;
    actor_set_sheet(boss->actor, "intro");
    if (boss->actor->done){
        boss->movement = Time.currentTime;
        boss->has_spawn = !boss->has_spawn;
        boss->actor->invincible = false;
        boss->actor->castShadow = true;
        boss->actor->shield = -1;
        boss->can_attack = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void wait_time(entity_t *evil)
{
    if (evil->has_spawn || Time.currentTime - evil->last_action < 2000)
        return;
    evil->has_spawn = true;
    evil->last_action = Time.currentTime;
    evil->can_attack = true;
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
        update_vfx(evil);
    } else {
        wait_time(evil);
        if (!evil->has_spawn)
            return;
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
