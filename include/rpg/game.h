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

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
typedef enum weapon_type_e {
    weaponLaser,
    weaponBullet,
    weaponMelee,
    weaponExplosive,
    WEAPON_TYPE_COUNT
} weapon_type_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \param sender
/// \param origin
/// \param destination
///
///////////////////////////////////////////////////////////////////////////////
typedef struct bullet_s {
    uint_t sender;
    sfSprite *sprite;
    v2f_t origin;
    v2f_t destination;
    v2f_t position;
    uint_t destroyed;
    uint_t rect_sprite;
    uint_t num_sheet;
    uint_t size_max_x;
    uint_t begin;
    sfCircleShape *area;
} bullet_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \param type
/// \param ammos
/// \param damage
/// \param firerate
///
///////////////////////////////////////////////////////////////////////////////
typedef struct weapon_s {
    weapon_type_t type;
    uint_t ammos;
    uint_t damage;
    float firerate;
} weapon_t;

extern struct bullet_list_s {
    bullet_t **array;
    uint_t count;
} Bullet_List;
///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
extern struct player_s {
    actor_t *ref;
    v2f_t velocity;
} Player;

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \param evt
///
///////////////////////////////////////////////////////////////////////////////
void game_loop(void);
bullet_t *bullet_creation(uint_t sender, uint_t size_rect, uint_t spritesheet,
    uint_t size_max);
void draw_bullets(void);
void destroy_bullet(bullet_t *bullet);

#endif /* !GAME_H_ */
