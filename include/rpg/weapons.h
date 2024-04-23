/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** weapons
*/

#ifndef WEAPONS_H_
    #define WEAPONS_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief all current weapon types available to players/enemies
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
/// \brief TODO:
///
/// \param sender       TODO:
/// \param origin       TODO:
/// \param destination  TODO:
///
///////////////////////////////////////////////////////////////////////////////
typedef struct bullet_s {
    uint_t sender;
    sfSprite *sprite;
    v2f_t origin;
    v2f_t destination;
    v2f_t position;
    bool_t destroyed;
    uint_t rect_sprite;
    uint_t num_sheet;
    uint_t size_max_x;
    uint_t begin;
    sfCircleShape *area;
} bullet_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param type         TODO:
/// \param ammos        TODO:
/// \param damage       TODO:
/// \param firerate     TODO:
///
///////////////////////////////////////////////////////////////////////////////
typedef struct weapon_s {
    weapon_type_t type;
    uint_t ammos;
    uint_t damage;
    float firerate;
} weapon_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param array        TODO:
/// \param count        TODO:
///
///////////////////////////////////////////////////////////////////////////////
extern struct bullet_list_s {
    bullet_t **array;
    uint_t count;
} Bullet_List;

///////////////////////////////////////////////////////////////////////////////
/// \brief create new bullets when players and enemies engage in shooting.
///
/// \param sender       The bullet id (who is the shooter?)
/// \param size_rect    The size of the first sprite
/// \param sprite_shett Number of sprite_sheet
/// \param size_max     The maximum size of the sprite_sheet
///
/// \return TODO:
///
///////////////////////////////////////////////////////////////////////////////
bullet_t *bullet_creation(uint_t sender, uint_t size_rect, uint_t spritesheet,
    uint_t size_max);

///////////////////////////////////////////////////////////////////////////////
/// \brief Updates all general information on all bullets.
///
/// Starts off by rendering the bullet and updating its position and velocity.
/// once done it checks for collision, and then deletes all unwanted bullets.
///
///////////////////////////////////////////////////////////////////////////////
void bullet_update(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Verifies collision and bullet distance.
///
/// If one of those condition are met. Bullet will enter destroyed mode, and
/// will be skipped during bullet update, and then deleted.
///
/// \param bullet       the sprite_sheet of the bullet.
///
/// \return TODO:
///
///////////////////////////////////////////////////////////////////////////////
bool_t bullet_collision(bullet_t *bullet);

///////////////////////////////////////////////////////////////////////////////
/// \brief destroy bullets when they hit their targets or get out of the
/// circle.
///
/// \param bullet       the sprite_sheet of the bullet.
///
///////////////////////////////////////////////////////////////////////////////
void remove_bullet(bullet_t *bullet);


#endif /* !WEAPONS_H_ */
