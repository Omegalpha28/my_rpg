/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** action
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"


///////////////////////////////////////////////////////////////////////////////
static void explosive_damage(actor_t *act)
{
    if (DASH && Player.ref == act)
        return;
    act->health -= (Player.ref == act) ? 1 : 60;
    act->damaged = true;
}

///////////////////////////////////////////////////////////////////////////////
void bomb_hit(v2f_t bomb_pos, char *explosion_name)
{
    effect_t *bomb = find_effect(explosion_name);
    recti_t bomb_mask = bomb->self->self->mask;

    bomb_mask.width /= 2.0f;
    bomb_mask.height /= 2.0f;
    bomb->framerate = FRAME_PER_MS(16);
    sfx(SFX_BOMB);
    for (uint_t i = 0; i < Pool.actorCount; i++){
        if (collision_hit(bomb_mask,
        Pool.actors[i]->self->sheets[Pool.actors[i]->sheetId]->image->mask,
        bomb_pos, Pool.actors[i]->position))
        explosive_damage(Pool.actors[i]);
    }
}
