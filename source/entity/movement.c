/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** movement
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Generates a new position based on minimum range and maximum range.
///
/// \param origin       Current vector position from which the new position
///                     will be generated from.
/// \param min_range    The minimum distance from the origin point to the new
///                     position.
/// \param max_range    The maximum distance from the origin point to the new
///                     position.
///
/// \return New generated random position vector.
///
///////////////////////////////////////////////////////////////////////////////
v2f_t rand_pos(v2f_t origin, int min_range, int max_range)
{
    float length = (float)(rand() % (max_range - min_range)) + min_range;

    origin.x = (rand() % 2) ? origin.x + length : origin.x - length;
    origin.y = (rand() % 2) ? origin.y + length : origin.y - length;
    return (origin);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Branch allowing for Patrolling behavioral movement.
///
/// generates a new position to idly walk to while checking its surroundings.
///
/// \param evil         Entity in patrol mode.

///////////////////////////////////////////////////////////////////////////////
void patrolling(entity_t *evil)
{
    float distance;
    v2f_t move;

    if (equal2f(evil->wanted_position, evil->actor->position)){
            evil->wanted_position = rand_pos(evil->actor->position, 30, 50);
        }
    distance = distance2f(evil->wanted_position, evil->actor->position);
    move = movetowards2f(evil->actor->position, evil->wanted_position,
        (evil->speed * Time.deltaTime) / 25);
    evil->actor->scale.x = move.x - evil->actor->position.x > 0 ? 1.0f : -1.0f;
    evil->actor->position = move;
    actor_set_anim(evil->actor, "walk");
}

///////////////////////////////////////////////////////////////////////////////
void enemy_movement(entity_t *evil)
{
    if (evil->status == Patrol)
        patrolling(evil);
}
