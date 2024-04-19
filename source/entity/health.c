/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** death
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Once animation is done, stop drawing.
///
/// \param evil         Entity in patrol mode.
///
///////////////////////////////////////////////////////////////////////////////
static void termination(entity_t *evil)
{
    printf("getting terminated\n");
    if (evil->actor->done && evil->actor->draw){
        if (evil->is_dammaged)
            evil->is_dammaged = !evil->is_dammaged;
        else
            evil->actor->draw = !evil->actor->draw;
    }
}

///////////////////////////////////////////////////////////////////////////////
void health_examination(entity_t *evil)
{
    if (evil->is_dammaged)
        actor_set_anim(evil->actor, "damage");
    if (evil->health <= 0 && !evil->dead && !evil->is_dammaged){
        evil->dead = !evil->dead;
        actor_set_anim(evil->actor, "death");
    }
    if (evil->dead || evil->is_dammaged)
        termination(evil);
}
