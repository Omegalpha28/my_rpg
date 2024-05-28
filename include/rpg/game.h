/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "rpg.h"
    #include "weapons.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param gems         TODO:
/// \param cookies      TODO:
/// \param doraditosBlue TODO:
/// \param doraditos    TODO:
/// \param eldritchMeats TODO:
/// \param fishs        TODO:
/// \param honeyCombs   TODO:
/// \param lettuces     TODO:
/// \param mushrooms    TODO:
/// \param salts        TODO:
/// \param happiness    TODO:
///
///////////////////////////////////////////////////////////////////////////////
typedef struct purse_s {
    uint_t gems;
    uint_t cookies;
    uint_t doraditosBlue;
    uint_t doraditos;
    uint_t eldritchMeats;
    uint_t fishs;
    uint_t honeyCombs;
    uint_t lettuces;
    uint_t mushrooms;
    uint_t salts;
    uint_t happiness;
} purse_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param ref          TODO:
/// \param velocity     TODO:
/// \param last_velocity TODO:
/// \param shakeOffset  TODO:
/// \param shakeStartng TODO:
/// \param shakeIntensity TODO:
/// \param shakeDuration TODO:
/// \param shaking      TODO:
/// \param viewCenter   TODO:
/// \param weapon       TODO:
/// \param inventor     TODO:
/// \param mag          TODO:
/// \param max_bullet   TODO:
/// \param speed        TODO:
/// \param num_shoot    TODO:
/// \param shoot_time   TODO:
/// \param canInteract  TODO:
/// \param lastAction   TODO:
/// \param reloading    TODO:
/// \param blocked      TODO:
/// \param purse        TODO:
///
///////////////////////////////////////////////////////////////////////////////
extern struct player_s {
    actor_t *ref;
    v2f_t velocity;
    v2f_t last_velocity;
    v2f_t shakeOffset;
    ulong_t shakeStarting;
    float shakeIntensity;
    ulong_t shakeDuration;
    bool_t shaking;
    v2f_t viewCenter;
    weapon_enum_t weapon;
    weapon_enum_t inventor[2];
    uint_t mag[2];
    uint_t max_bullet;
    float speed;
    uint_t num_shoot;
    uint_t shoot_time;
    bool_t canInteract;
    ulong_t lastAction;
    bool_t reloading;
    bool_t blocked;
    purse_t purse;
} Player;

///////////////////////////////////////////////////////////////////////////////
/// \brief Check the program flags
///
/// \param argc         The number of arguments
/// \param argv         The array of arguments
///
///////////////////////////////////////////////////////////////////////////////
void check_program_flags(int argc, warray_t argv);

///////////////////////////////////////////////////////////////////////////////
/// \brief Handle drawing
///
///////////////////////////////////////////////////////////////////////////////
void draw(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Handle game loop
///
///////////////////////////////////////////////////////////////////////////////
void game_loop(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Interaction with a weapon
///
/// \param obj          The object to interact with
///
///////////////////////////////////////////////////////////////////////////////
void pickup(interactable_t *obj);

#endif /* !GAME_H_ */
