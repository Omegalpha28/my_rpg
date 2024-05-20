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

    #define ENTITY_REMOVE 10
    #define MAX_ATTACK 10
    #define CTHULU_TODO 3




///////////////////////////////////////////////////////////////////////////////
/// \brief All possible status' for entities
///
///////////////////////////////////////////////////////////////////////////////
typedef enum status_e {
    Patrol,
    Agressive,
    Fear,
    Dazed,
    ranger,
    STATUS_COUNT,
} status_t;


///////////////////////////////////////////////////////////////////////////////
/// \brief enumeration of all possible attack types.
///
///////////////////////////////////////////////////////////////////////////////
typedef enum attack_types_e {
    Dash,
    Shooter,
    Jumper,
    Bomber,
    sniper,
    ATTACK_COUNT,
}attack_types_t;


///////////////////////////////////////////////////////////////////////////////
/// \brief structure containing pertinent information on each enemy
///
///////////////////////////////////////////////////////////////////////////////
typedef struct entity_s {
    actor_t *actor;
    ulong_t last_action;
    bool_t has_spawn;
    float speed;
    float attack_radius;
    bool_t is_attack;
    status_t status;
    v2f_t wanted_position;
    attack_types_t attack_types;
    float insight;
    uint_t dizzy;
    float collision;
    bool_t can_attack;
    uint_t cooldown;
    bool_t attack_started;
    uint_t movement;
} entity_t;


typedef enum boss_index_e {
    BOSS_Crabington,
    BOSS_Cthulu,
    BOSS_COUNT,
} boss_index_t;

typedef enum Boss_attack_types_e {
    DASH_ATTACK,
    MOUTH_BLASTER,
    BUBBLE_DOME,
    BULLET_HELL,
    SPIKE_TRAP,
    BOSS_ATTACK_COUNT,
} Boss_attack_types_t;

typedef struct Boss_list_s {
    actor_t *actor;
    ulong_t last_action;
    float speed;
    bool_t is_attack;
    bool_t can_attack;
    uint_t cooldown;
    uint_t movement;
    int attack_amount;
    uint_t dizzy;
    int bstat_position;
    Boss_attack_types_t attack_list[MAX_ATTACK];
    int curr_phase;
} boss_t;

typedef struct Boss_stat_s {
    int attack_amount;
    float speed;
    int health;
    int creature_id;
    uint_t dizzy;
    Boss_attack_types_t attack_list[MAX_ATTACK];
} Boss_stats_t;

static const Boss_stats_t B_Stats[BOSS_COUNT] = {
    {3, 5, 100, 2, 3000, {0, 1, 2}},    //Crabington
    {5, 0, 100, 0, 0, {0, 1, 2, 3, 4}}, //Cthulu
};


///////////////////////////////////////////////////////////////////////////////
/// \brief Global structure containing all information on enemy entities.
///
///////////////////////////////////////////////////////////////////////////////
extern struct entity_list_s {
    entity_t **array;
    boss_t **boss_array;
    int count;
    int bcount;
    entity_t *toRemove[ENTITY_REMOVE];
} Entities;


///////////////////////////////////////////////////////////////////////////////
/// \brief Structure stat for of each creature
///
///////////////////////////////////////////////////////////////////////////////
typedef struct creature_stats_s {
    uint_t health;
    float_t speed;
    float_t attack_radius;
    float_t insight;
    attack_types_t attack_types;
    uint_t dizzy;
} creature_stats_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief setting the basic stat for each creature
///
///////////////////////////////////////////////////////////////////////////////
static const creature_stats_t Stats[CREATURE_COUNT] = {
    {100, 0, 0, 0, 0, 0},                       //player
    {100, 0.7, 0, 0, Bomber, 1000},             //duck
    {100, 0.5, 0, 100, Dash, 3000},             //crab boss
    {100, 0.4f, 65.0f, 100.0f, sniper, 0},      //bald rat
    {100, 0, 0, 0, 0, 0},                       //dummy
    {100, 0, 0, 0, Dash, 3000},                 //baby crab (elite)
    {30, 0.5f, 0.0f, 100.0f, Dash, 0},          //caterkillah
    {100, 0.4f, 50.0f, 100.0f, Shooter, 0},     //cinnamon rat
    {100, 0.5f, 50.0f, 100.0f, Jumper, 0},      //baby caiman
    {100, 0.4f, 125.0f, 175.0f, Shooter, 0},    //elite racoon
    {100, 0.4f, 100.0f, 150.0f, Shooter, 0},    //elite fox
    {100, 0.4f, 60.0f, 100.0f, Shooter, 0},     //Brat
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


///////////////////////////////////////////////////////////////////////////////
/// \brief Calls upon all the branches for the updating of each entity.
///
/// Calls upon movement, then all actions. Once done it calls the drawing
/// function.
///
///////////////////////////////////////////////////////////////////////////////
void update_entity(void);


///////////////////////////////////////////////////////////////////////////////
/// \brief Calls upon all possible movement branch.
///
/// \param evil         Pointer to Entity info structure.
///
///////////////////////////////////////////////////////////////////////////////
void enemy_movement(entity_t *evil);


///////////////////////////////////////////////////////////////////////////////
/// \brief Remove an entity from the list
///
/// \param ent          The entity to remove
///
///////////////////////////////////////////////////////////////////////////////
void remove_entity(entity_t *ent);


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
v2f_t rand_pos(v2f_t origin, int min_range, int max_range);


///////////////////////////////////////////////////////////////////////////////
/// \brief Generates a new position based on minimum range and maximum range.
///
/// the random position will always be on one of the 4 cardinal directions.
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
v2f_t flee_rand_pos(v2f_t origin, int min_range, int max_range);


///////////////////////////////////////////////////////////////////////////////
/// \brief Checks entities vitals.
///
/// \param evil         Entity in patrol mode.
///
///////////////////////////////////////////////////////////////////////////////
void health_examination(entity_t *evil);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calls upon all possible acion branch.
///
/// \param evil         Pointer to Entity info structure.
///
///////////////////////////////////////////////////////////////////////////////
void enemy_action(entity_t *evil);


///////////////////////////////////////////////////////////////////////////////
/// \brief checks all possible collisions.
///
///////////////////////////////////////////////////////////////////////////////
void update_collisions(void);


///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new boss based on a creature and a position
///
/// \param creature     The reference creature for the actor
/// \param position     The default position of the actor
///
/// \return The newly created boss.
///
///////////////////////////////////////////////////////////////////////////////
boss_t *boss_create(creature_t *creature, v2f_t position);


///////////////////////////////////////////////////////////////////////////////
/// \brief Remove a boss from the list
///
/// \param ent          The entity to remove
///
///////////////////////////////////////////////////////////////////////////////
void remove_boss(boss_t *ent);


///////////////////////////////////////////////////////////////////////////////
/// \brief Does all movement checks for the bosses.
///
///////////////////////////////////////////////////////////////////////////////
void boss_movement(boss_t *boss);


///////////////////////////////////////////////////////////////////////////////
/// \brief Does all action checks for the bosses.
///
///////////////////////////////////////////////////////////////////////////////
void boss_action(boss_t *boss);

#endif /* !ENTITY_H_ */
