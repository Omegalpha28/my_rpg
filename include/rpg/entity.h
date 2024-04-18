/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity
*/

#ifndef ENTITY_H_
    #define ENTITY_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "rpg.h"



///////////////////////////////////////////////////////////////////////////////
/// \brief All possible status' for entities
///
///////////////////////////////////////////////////////////////////////////////

typedef enum status_e {
    Patrol,
    Agressive,
    Fear,
    Dazed,
    STATUS_COUNT,
} status_t;


typedef enum attack_types_e {
    Dash,
    Shooter,
    Jumper,
    Bomber,
    ATTACK_COUNT,
}attack_types_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief structure containing pertinent information on each enemy
///
///////////////////////////////////////////////////////////////////////////////
typedef struct entity_s {
    actor_t *actor;
    uint_t health;
    uint_t behavior;
    ulong_t last_action;
    bool_t has_spawn;
    float_t speed;
    float_t radius;
    bool_t is_attack;
    status_t status;
    v2f_t wanted_position;
    attack_types_t attack;
    float_t insight;
} entity_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Global structure containing all information on enemy entities.
///
///////////////////////////////////////////////////////////////////////////////
extern struct entity_list_s {
    entity_t **array;
    uint_t count;
} Entities;

///////////////////////////////////////////////////////////////////////////////
/// \brief Structure stat for of each creature
///
///////////////////////////////////////////////////////////////////////////////
typedef struct creature_stats_s {
    uint_t health;
    uint_t behavior;
    float_t speed;
    float_t radius;
    float_t insight;
    attack_types_t attack;
} creature_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief setting the basic stat for each creature
///
///////////////////////////////////////////////////////////////////////////////
static const creature_stats_t Stats[CREATURE_COUNT] = {
    {100, 0, 0, 0, 0, 0},                   //player
    {100, 0, 0, 0, 0, 0},                   //duck
    {100, 0, 0, 0, 0, 0},                   //crab boss
    {100, 0, 0, 0, 0, 0},                   //bald rat
    {100, 0, 0, 0, 0, 0},                   //dummy
    {100, 0, 0, 0, 0, 0},                   //baby crab
    {100, 0, 0.4f, 75.0f, 100.0f, Dash},    //caterkillah
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new entitty base on a creature and a position
///
/// \param creature     The reference creature for the actor
/// \param position     The default position of the actor
///
/// \return The newly created entity
///
///////////////////////////////////////////////////////////////////////////////
entity_t *entity_create(creature_t *creature, v2f_t position);

void update_entity(void);

void enemy_movement(entity_t *evil);

#endif /* !ENTITY_H_ */


/*

//player
//duck
//crab boss
//bald rat
//dummy
//baby crab
//caterkillah

ai state graph

new:

attack_goal

min attack_distance,
max attack_distance,
cooldown,
attack length.
status

*/
