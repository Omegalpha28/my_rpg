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
typedef enum weapons_enum_e {
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
} weapon_enum_t;

typedef enum fire_type_e {
    FIRE_SINGLE,
    FIRE_BURST,
    FIRE_AUTO,
    FIRE_TYPE_COUNT
} fire_type_t;

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

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// TODO:
///
///////////////////////////////////////////////////////////////////////////////
typedef struct bullet_stat_s {
    text_bullet_t base;
    text_bullet_t impactWall;
    text_bullet_t impactEnemy;
    text_bullet_t disappear;
    float range;
    float speed;
} bullet_stat_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
typedef enum bullet_list_e {
    BULLET_AK,
    BULLET_SHOTGUN,
    BULLET_SNIPER,
    BULLET_SMG,
    BULLET_PISTOL,
    BULLET_ARROW,
    BULLET_MELEE,
    BULLET_KATANA,
    BULLET_MOTORBLADE,
    BULLET_COUNT
} bullet_list_t;

///////////////////////////////////////////////////////////////////////////////
static const bullet_stat_t BULLET_STATS[BULLET_COUNT] = {
    {T_AK_BASE, T_AK_IMPACT_WALL, T_AK_IMPACT_ENEMY, T_AK_DISAPPEAR,
        200.0f, 10.0f},
    {T_SHOTGUN_BASE, T_SHOTGUN_IMPACT_WALL, T_SHOTGUN_IMPACT_ENEMY,
        T_SHOTGUN_DISAPPEAR, 100.0f, 10.0f},
    {T_SNIPER_BASE, T_SNIPER_IMPACT_WALL, T_SNIPER_IMPACT_ENEMY,
        T_SHOTGUN_DISAPPEAR, 500.0f, 10.0f},
    {T_SMG_BASE, T_SMG_IMPACT_WALL, T_SMG_IMPACT_ENEMY,
        T_SMG_DISAPPEAR, 500.0f, 10.0f},
    {T_PISTOL_BASE, T_PISTOL_IMPACT_WALL, T_PISTOL_IMPACT_ENEMY,
        T_PISTOL_DISAPPEAR, 200.0f, 10.0f},
    {T_ARROW_BASE, T_ARROW_STUCK_WALL, T_ARROW_IMPACT_ENEMY, T_ARROW_CHARGED,
        300.0f, 10.0f},
    {T_SWORD, T_SWORD, T_SWORD, T_SWORD, 50.0f, 0.0f},
    {T_KATANA_PARTICLE, T_KATANA_PARTICLE, T_KATANA_PARTICLE,
        T_KATANA_PARTICLE, 50.0f, 0.0f},
    {T_MOTORBLADE_PARTICLE, T_MOTORBLADE_PARTICLE, T_MOTORBLADE_PARTICLE,
        T_MOTORBLADE_PARTICLE, 50.0f, 0.0f},
};

///////////////////////////////////////////////////////////////////////////////
typedef struct weapon_s {
    weapon_type_t type;
    fire_type_t fireType;
    uint_t ammoPerMag;
    uint_t damage;
    float firerate;
    uint_t bulletType;
    float shakingIntensity;
} weapon_t;


static const weapon_t WEAPON_STATS[WEAPON_COUNT] = {
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 1, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 1, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 1, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 1, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 1, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 0, 10, 20, BULLET_MELEE, 10.0f},
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 0, 10, 20, BULLET_KATANA, 10.0f},
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 0, 10, 20, BULLET_MELEE, 10.0f},
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 0, 10, 20, BULLET_MELEE, 10.0f},
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 0, 10, 20, BULLET_MOTORBLADE, 10.0f},
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 20, 10, 20, BULLET_PISTOL, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 20, 10, 20, BULLET_SHOTGUN, 10.0f},
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 20, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 20, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 20, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 20, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 20, 10, 20, BULLET_SMG, 10.0f},
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 20, 10, 20, BULLET_SNIPER, 10.0f},
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 20, 10, 20, BULLET_SNIPER, 10.0f},
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 20, 10, 20, BULLET_SNIPER, 10.0f},
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 20, 10, 20, BULLET_SNIPER, 10.0f},
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 20, 10, 20, BULLET_SNIPER, 10.0f},
};

///////////////////////////////////////////////////////////////////////////////
/// \brief verifying if every bullet hit their target or has an impact with
/// someone or something else.
///
/// \return TODO:
///
///////////////////////////////////////////////////////////////////////////////
void bullet_collision(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief destroy bullets when they hit their targets or get out of the
/// circle.
///
/// \param sender       The shooter.
/// \param destination  The vector to design the target.
/// \param weapon       The weapon used by the shooter.
///
///////////////////////////////////////////////////////////////////////////////
void create_bullet(actor_t *sender, v2f_t destination, weapon_enum_t weapon);

///////////////////////////////////////////////////////////////////////////////
/// \brief destroy bullets when they hit their targets or get out of the
/// circle.
///
/// \param bullet       the sprite_sheet of the bullet.
///
///////////////////////////////////////////////////////////////////////////////
void remove_bullet(bullet_t *bullet);

///////////////////////////////////////////////////////////////////////////////
/// \brief Renders a bullet, updating its position based on its origin,
/// destination, and velocity.
///
/// \param              bullet pointer to bullet structure.
///
///////////////////////////////////////////////////////////////////////////////
void bullet_render(bullet_t *bullet);

///////////////////////////////////////////////////////////////////////////////
/// \brief Drawing bullets.
///
///
///////////////////////////////////////////////////////////////////////////////
void draw_bullet(void);

void bullet_render(bullet_t *bullet);
#endif /* !WEAPONS_H_ */
