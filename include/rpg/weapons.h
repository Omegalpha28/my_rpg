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
/// \brief All current weapon types available to players/enemies
///
///////////////////////////////////////////////////////////////////////////////
typedef enum weapon_type_e {
    WEAPON_TYPE_EXPLOSIVE,
    WEAPON_TYPE_LASER,
    WEAPON_TYPE_MELEE,
    WEAPON_TYPE_PISTOL,
    WEAPON_TYPE_RIFLE,
    WEAPON_TYPE_SHOTGUN,
    WEAPON_TYPE_SMG,
    WEAPON_TYPE_SNIPER,
    WEAPON_TYPE_COUNT
} weapon_type_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief List of predefined weapons
///
///////////////////////////////////////////////////////////////////////////////
enum weapons_e {
    WEAPON_EXPLOSIVE_BUCCANEER,
    WEAPON_EXPLOSIVE_GRENADE,
    WEAPON_EXPLOSIVE_G_LAUNCHER,
    WEAPON_EXPLOSIVE_HAMMER_HEAD,
    WEAPON_EXPLOSIVE_HYDRA,
    WEAPON_LASER_BLASTER,
    WEAPON_LASER_REGULATOR,
    WEAPON_LASER_PHASER,
    WEAPON_LASER_ZAP_CANNON,
    WEAPON_LASER_RAYGUN,
    WEAPON_MELEE_AXELOTL,
    WEAPON_MELEE_KATANA,
    WEAPON_MELEE_BEHEADER,
    WEAPON_MELEE_SCYTHE,
    WEAPON_MELEE_MOTORBLADE,
    WEAPON_PISTOL_POND_EAGLE,
    WEAPON_PISTOL_TACTIC_GUN,
    WEAPON_PISTOL_TADPOLES,
    WEAPON_PISTOL_RATVOLVER,
    WEAPON_PISTOL_WINGERS,
    WEAPON_RIFLE_AK,
    WEAPON_RIFLE_KARBINE,
    WEAPON_RIFLE_COWPUP,
    WEAPON_RIFLE_SUPER_SHOOTER,
    WEAPON_RIFLE_BIG_AK,
    WEAPON_SHOTGUN_SAWED_OFF,
    WEAPON_SHOTGUN_SCATTERER,
    WEAPON_SHOTGUN_MOSSTOAD,
    WEAPON_SHOTGUN_TURBO_SHOTGUN,
    WEAPON_SHOTGUN_DOOMGUN,
    WEAPON_SMG_U_Z_1,
    WEAPON_SMG_PEW_PEWER,
    WEAPON_SMG_VERMINATOR,
    WEAPON_SMG_B_BANGER,
    WEAPON_SMG_GATORINGA,
    WEAPON_SNIPER_HOGGEN,
    WEAPON_SNIPER_KALAS,
    WEAPON_SNIPER_CRABBER,
    WEAPON_SNIPER_SUC_2,
    WEAPON_SNIPER_B_A_S,
    WEAPON_COUNT
};

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
/// \param type          TODO:
/// \param ammos         TODO:
/// \param damage        TODO:
/// \param firerate      TODO:
/// \param weapon_type_t TODO:
/// \param weapon_e      TODO:
///
///////////////////////////////////////////////////////////////////////////////
typedef struct weapon_s {
    weapon_type_t type;
    sfSprite *sprite;
    uint_t ammos;
    uint_t damage;
    float_t firerate;
    bool_t enable;
    v2f_t origin;
    v2f_t destination;
    v2f_t position;
    recti_t rect;
} weapon_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param type          TODO:
/// \param ammos         TODO:
/// \param damage        TODO:
/// \param firerate      TODO:
/// \param weapon_type_t TODO:
/// \param weapon_e      TODO:
///
///////////////////////////////////////////////////////////////////////////////
extern struct weapon_list_s {
    weapon_t **weapon;
    uint_t count;
} Weapon_List;
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
/// \brief initialize weapons.
///
/// \return TODO:
///
///////////////////////////////////////////////////////////////////////////////
void init_weapons(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief enable and disable weapons.
///
/// \return TODO:
///
///////////////////////////////////////////////////////////////////////////////
void activate_weapon(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief destroy bullets when they hit their targets or get out of the
/// circle.
///
/// \param bullet       the sprite_sheet of the bullet.
///
///////////////////////////////////////////////////////////////////////////////
void remove_bullet(bullet_t *bullet);


#endif /* !WEAPONS_H_ */
