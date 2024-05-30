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
    Sniper,
    Boss,
    Spinjutsu,
    ATTACK_COUNT,
}attack_types_t;


///////////////////////////////////////////////////////////////////////////////
/// \brief enumeration of all bosses.
///
///////////////////////////////////////////////////////////////////////////////
typedef enum boss_index_e {
    BOSS_Crabington,
    BOSS_Cthulu,
    BOSS_COUNT,
} boss_index_t;



///////////////////////////////////////////////////////////////////////////////
/// \brief enumeration of all possible attack types for bosses.
///
///////////////////////////////////////////////////////////////////////////////
typedef enum Boss_attack_types_e {
    DASH_ATTACK,
    MOUTH_BLASTER,
    BUBBLE_DOME,
    BULLET_HELL,
    SPIKE_TRAP,
    BOSS_ATTACK_COUNT,
} Boss_attack_types_t;


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
    bool_t attack_started;
    weapon_enum_t weapon;
    uint_t movement;
    int attack_amount;
    Boss_attack_types_t attack_list[MAX_ATTACK];
    int bstat_pos;
    int curr_phase;
    uint_t firerate;
    uint_t ball_count;
    uint_t bounce;
    v2f_t vector;
    v2f_t c4_pos;
    uint_t cooldown;
    uint_t timebomb;
} entity_t;


///////////////////////////////////////////////////////////////////////////////
/// \brief Structure stat for boss' attack type.
///
///////////////////////////////////////////////////////////////////////////////
typedef struct Boss_stat_s {
    int attack_amount;
    Boss_attack_types_t attack_list[MAX_ATTACK];
} Boss_stats_t;


///////////////////////////////////////////////////////////////////////////////
/// \brief Structure stat for of each -*
///
///////////////////////////////////////////////////////////////////////////////
static const Boss_stats_t B_Stats[BOSS_COUNT] = {
    {3, {DASH_ATTACK, MOUTH_BLASTER, BUBBLE_DOME}},
    {5, {DASH_ATTACK, MOUTH_BLASTER, BUBBLE_DOME, BULLET_HELL, SPIKE_TRAP}},
};


///////////////////////////////////////////////////////////////////////////////
/// \brief Global structure containing all information on enemy entities.
///
///////////////////////////////////////////////////////////////////////////////
extern struct entity_list_s {
    entity_t **array;
    int count;
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
    enum weapons_enum_e weapon;
    uint_t firerate;
    uint_t ball_count;
    bool_t hideWeapon;
} creature_stats_t;


///////////////////////////////////////////////////////////////////////////////
/// \brief setting the basic stat for each creature
///
///////////////////////////////////////////////////////////////////////////////
static const creature_stats_t Stats[CREATURE_COUNT] = {
    {150, 0, 0, 0, 0, 0, 0, 0, 1, 0},                        //player
    {120, 0.8, 0, 0, Bomber, 1000, 1, 3000, 1, 1},              //duck
    {950, 0.5, 0, 100, Boss, 3000, WEAPON_SHOTGUN_SKULL, 1000, 12, 1}, //Cboss
    {85, 0.5f, 80.0f, 200.0f, Sniper, 0, 35, 4000, 1, 0},      //bald rat
    {120, 0.4f, 0.0f, 100.0f, Spinjutsu, 3000, -1, 2000, 0, 0}, //baby crab
    {120, 0, 0, 0, 0, 0, 0, 0, 1, 1},                        //dummy
    {72, 0.6f, 0.0f, 100.0f, Dash, 0, 12, 0, 0, 1},          //caterkillah
    {90, 0.5f, 100.0f, 120.0f, Shooter, 0, 45, 3000, 1, 0}, //cinnamon rat
    {60, 0.6f, 50.0f, 100.0f, Jumper, 0, 14, 2000, 1, 1}, //baby caiman
    {150, 0.5f, 150.0f, 225.0f, Shooter, 0, 29, 3000, 7, 0}, //elite racoon
    {150, 0.5f, 160.0f, 250.0f, Shooter, 0, 31, 2000, 1, 0}, //elite fox
    {85, 0.5f, 75.0f, 110.0f, Shooter, 0, 5, 2000, 5, 0}, //Brat
    {175, 0.7f, 100.0f, 1000.0f, Sniper, 0, 31, 1750, 11, 0}, // sign boss
    {INT_MAX, 0, 0, 0, 0, 0, 0, 0, 1, 1}, // pnjs
    {INT_MAX, 0, 0, 0, 0, 0, 0, 0, 1, 1}, // chests
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
/// \brief Does all movement checks for the bosses.
///
///////////////////////////////////////////////////////////////////////////////
void boss_movement(entity_t *boss);

///////////////////////////////////////////////////////////////////////////////
/// \brief Does all action checks for the bosses.
///
///////////////////////////////////////////////////////////////////////////////
void boss_action(entity_t *boss);


///////////////////////////////////////////////////////////////////////////////
/// \brief fires off the neccessary amount of bullets.
///
/// \param evil         Pointer to the enemy shooting.
/// \param ball_amount  Amount of balls needed to be shot.
/// \param offset       distance between each ball if multishot is
///                     accounted for.
///
///////////////////////////////////////////////////////////////////////////////
void firing(entity_t *evil, uint_t ball_amount, int offset);


///////////////////////////////////////////////////////////////////////////////
/// \brief Simulates the movement and finds the position right before the wall
/// and "bounces off" the wall.
///
/// \param crab         Pointer to the crab getting simulated.
///
///////////////////////////////////////////////////////////////////////////////
void get_wanted_position(entity_t *crab);


///////////////////////////////////////////////////////////////////////////////
/// \brief Gets positions and set the movement vector for the spinning. Then it
/// calls upon get position for the simulation of movement.
///
/// \param evil         Pointer to entity learning spinjujtsu.
///
///////////////////////////////////////////////////////////////////////////////
void spinning_movement(entity_t *evil);


///////////////////////////////////////////////////////////////////////////////
/// \brief checks if enemy is in range and damages the hit entity.
///
/// \param evil         Pointer to entity doing collision damage attack.
///
///////////////////////////////////////////////////////////////////////////////
void dash_collision_hit(entity_t *evil);


///////////////////////////////////////////////////////////////////////////////
/// \brief does the check for the sfx bubble.
///
/// \param evil         Pointer to crab entity with its bubble.
///
///////////////////////////////////////////////////////////////////////////////
void domain_expansion(entity_t *crab);


///////////////////////////////////////////////////////////////////////////////
/// \brief When sir crabington needs to go berserk.
///
/// \param crab         Pointer to crab entity structure.
///
///////////////////////////////////////////////////////////////////////////////
void enrage(entity_t *crab);


///////////////////////////////////////////////////////////////////////////////
/// \brief Checks if 2 masks are in collision with each other.
///
/// \param attack_mask
/// \param recipient_mask
/// \param attack_pos
/// \param recipient_pos
///
/// \return 1 if collisions are present, 0 if not.
///
///////////////////////////////////////////////////////////////////////////////
bool_t collision_hit(recti_t attack_mask, recti_t recipient_mask,
    v2f_t attack_pos, v2f_t recipient_pos);


///////////////////////////////////////////////////////////////////////////////
/// \brief checks if explosion has hit any entities and does damage
/// accordingly.
///
/// \param bomb_pos
/// \param explosion_name
///
///////////////////////////////////////////////////////////////////////////////
void bomb_hit(v2f_t bomb_pos, char *explosion_name);

#endif /* !ENTITY_H_ */
