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
    WEAPON_NO = -1,
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
    WEAPON_RIFLE_NERF,
    WEAPON_SMG_BADGER,
    WEAPON_MELEE_CLEAVER,
    WEAPON_BOSS_CTHULU,
    WEAPON_PISTOL_RAYGUN,
    WEAPON_PISTOL_REVOLVER,
    WEAPON_PISTOL_FLAREGUN,
    WEAPON_SNIPER_CROSSBOW,
    WEAPON_PISTOL_ASSASSIN,
    WEAPON_PISTOL_HAND,
    WEAPON_PISTOL_STARLORD,
    WEAPON_SMG_NAILGUN,
    WEAPON_SHOTGUN_PLANT,
    WEAPON_SNIPER_DRAGUNOV,
    WEAPON_PISTOL_GRAPLING,
    WEAPON_RIFLE_PARINO,
    WEAPON_SNIPER_ARTIC,
    WEAPON_MELEE_IRONFIST,
    WEAPON_MELEE_BOOMERANG,
    WEAPON_MELEE_SAURON,
    WEAPON_MELEE_LIGHTSABER,
    WEAPON_LASER_PARTY,
    WEAPON_BOSS_TURTLE,
    WEAPON_MELEE_RACKET,
    WEAPON_SHOTGUN_BOLTACTION,
    WEAPON_SHOTGUN_SKULL,
    WEAPON_MELEE_GUITAR,
    WEAPON_BOSS_SNAKE,
    WEAPON_MELEE_BAMBO,
    WEAPON_SNIPER_BONE_CROSSBOW,
    WEAPON_MELEE_FISHING_ROD,
    WEAPON_COUNT
} weapon_enum_t;

///////////////////////////////////////////////////////////////////////////////
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
    bool_t invert;
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
    BULLET_ROCKET,
    BULLET_COUNT
} bullet_list_t;

///////////////////////////////////////////////////////////////////////////////
static const bullet_stat_t BULLET_STATS[BULLET_COUNT] = {
    {T_AK_BASE, T_AK_IMPACT_WALL, T_AK_IMPACT_ENEMY, T_AK_DISAPPEAR,
        150.0f, 10.0f, false},
    {T_SHOTGUN_BASE, T_SHOTGUN_IMPACT_WALL, T_SHOTGUN_IMPACT_ENEMY,
        T_SHOTGUN_DISAPPEAR, 100.0f, 10.0f, true},
    {T_SNIPER_BASE, T_SNIPER_IMPACT_WALL, T_SNIPER_IMPACT_ENEMY,
        T_SHOTGUN_DISAPPEAR, 500.0f, 30.0f, true},
    {T_SMG_BASE, T_SMG_IMPACT_WALL, T_SMG_IMPACT_ENEMY,
        T_SMG_DISAPPEAR, 500.0f, 10.0f, true},
    {T_PISTOL_BASE, T_PISTOL_IMPACT_WALL, T_PISTOL_IMPACT_ENEMY,
        T_PISTOL_DISAPPEAR, 200.0f, 10.0f, false},
    {T_ARROW_BASE, T_ARROW_STUCK_WALL, T_ARROW_IMPACT_ENEMY, T_ARROW_CHARGED,
        300.0f, 10.0f, false},
    {T_SWORD, T_SWORD, T_SWORD, T_SWORD, 50.0f, 0.0f, false},
    {T_KATANA_PARTICLE, T_KATANA_PARTICLE, T_KATANA_PARTICLE,
        T_KATANA_PARTICLE, 50.0f, 0.0f, false},
    {T_MOTORBLADE_PARTICLE, T_MOTORBLADE_PARTICLE, T_MOTORBLADE_PARTICLE,
        T_MOTORBLADE_PARTICLE, 50.0f, 0.0f, false},
    {T_ROCKET, T_ROCKET, T_ROCKET, T_ROCKET, 50.0f, 5.0f, false}
};

///////////////////////////////////////////////////////////////////////////////
typedef struct weapon_s {
    weapon_type_t type;
    fire_type_t fireType;
    uint_t ammoPerMag;
    uint_t damage;
    float firerate;
    bullet_list_t bulletType;
    float shakingIntensity;
    float shakingDuration;
    sfx_list_t sound;
    float reload_time;
} weapon_t;

///////////////////////////////////////////////////////////////////////////////
static const weapon_t WEAPON_STATS[WEAPON_COUNT] = {
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 25, 26, 0.6, BULLET_ROCKET, 7.5f,
        0.15f, SFX_BOMB, 2}, // BUCCANEER
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 20, 35, 1.2, BULLET_ROCKET, 7.5f,
        0.15f, SFX_BOMB, 2}, // GRENADE
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 35, 35, 0.5, BULLET_ROCKET, 7.5f,
        0.15f, SFX_BOMB, 2}, // GRENADE LAUNCHER
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 16, 60, 1.5, BULLET_ROCKET, 7.5f,
        0.15f, SFX_BOMB, 2}, // HAMMER HEAD
    {WEAPON_TYPE_EXPLOSIVE, FIRE_SINGLE, 24, 60, 2.5, BULLET_ROCKET, 7.5f,
        0.15f, SFX_BOMB, 2}, // HYDRA
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 200, 6, 0.15, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_LASER_BLASTER, 2}, // BLASTER
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 160, 6, 0.25, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_LASER_REGULATOR, 2}, // REGULATOR
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 150, 10, 0.7, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_LASER_ZAPCANNON, 2}, // PHASER
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 152, 12, 0.8, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_LASER_ZAPCANNON, 2}, // ZAP CANNON
    {WEAPON_TYPE_LASER, FIRE_SINGLE, 140, 8, 0.18, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_LASER_ZAPCANNON, 2}, // RAYGUN
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 30, 1.1, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_MELEE_AXELOTL, 2}, // AXELOTL
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 20, 0.8, BULLET_KATANA, 2.5f, 0.15f,
        SFX_WP_KATANA, 2}, // KATANA
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 20, 0.5, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_MELEE_BEHEADER, 2}, // BEHEADER
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 20, 0.8, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 2}, // SCYTHE
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 200, 7, 0.1, BULLET_MOTORBLADE, 2.5f,
        0.15f, SFX_WP_KNIFE, 2}, // MOTOR BLADE
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 9, 6, 0.15, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 2}, // POND EAGLE
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 200, 6, 0.12, BULLET_PISTOL, 2.5f,
        0.15f, SFX_WP_BERETTA, 2}, // TACTIC GUN
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 350, 4, 0.15, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_TADPOLES, 2}, // TADPOLES
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 160, 7, 0.1, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_RATVOLVER, 2}, // RATVOLVER
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 444, 4, 0.15, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 2}, // WINGERS
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 35, 24, 0.8, BULLET_AK, 2.5f,
        0.15f, SFX_WP_AK, 2}, // AK
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 180, 7, 0.25, BULLET_AK, 2.5f,
        0.15f, SFX_WP_CARBINE, 2}, // KARBINE
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 210, 7, 0.33, BULLET_AK, 2.5f,
        0.15f, SFX_WP_AK, 2}, // COWPUP
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 200, 7, 0.3, BULLET_AK, 2.5f,
        0.15f, SFX_WP_RIFLE_SUPER, 2}, // SUPER SHOOTER
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 200, 10, 0.18, BULLET_AK, 2.5f,
        0.15f, SFX_WP_AK, 2}, // BIG AK
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 40, 5, 0.8, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_SHOTGUN, 2}, // SAWED OFF
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 6, 4, 0.4, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_SHOTGUN, 2}, // SCATTERER
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 50, 5, 0.5, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_SHOTGUN, 2}, // MOSSTOAD
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 150, 12, 1, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_SPAS, 2}, // TURBO SHOTGUN
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 64, 8, 0.6, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_DOOM, 2}, // DOOMGUN
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 250, 4, 0.25, BULLET_SMG, 2.5f, 0.15f,
        SFX_WP_UZI, 2}, // UZI
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 200, 3, 0.15, BULLET_SMG, 2.5f, 0.15f,
        SFX_WP_UZI, 2}, // PEW PEWER
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 300, 3, 0.15, BULLET_SMG, 2.5f, 0.15f,
        SFX_WP_MP5, 2}, // VERMINATOR
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 320, 3, 0.22, BULLET_SMG, 2.5f, 0.15f,
        SFX_WP_P90, 2}, // B BANGER
    {WEAPON_TYPE_SMG, FIRE_SINGLE, 400, 3, 0.08, BULLET_SMG, 2.5f, 0.15f,
        SFX_WP_GATLING, 2}, // GATORINGA
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 20, 10, 0.5, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_RIFLE, 2}, // HOGGEN
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 35, 24, 0.8, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_KALAS, 2}, // KALAS
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 50, 24, 0.5, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_RIFLE, 2}, // CRABBER
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 40, 35, 1, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_RIFLE, 2}, // SUC 2
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 30, 50, 0.85, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_RIFLE, 2}, // BAS
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 30, 6, 0.28, BULLET_AK, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // RIFLE_NERF
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 200, 9, 0.3, BULLET_SMG, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // SMG_BADGER
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 100, 25, 1.3, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // MELEE_CLEAVER
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 250, 8, 0.22, BULLET_AK, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // BOSS_CTHULU
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 30, 15, 0.5, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 3}, // PISTOL_RAYGUN
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 200, 6, 0.18, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 3}, // PISTOL_REVOLVER
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 150, 8, 0.35, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 3}, // PISTOL_FLAREGUN
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 200, 5, 0.9, BULLET_ARROW, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // SNIPER_CROSSBOW
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 200, 6, 0.25, BULLET_PISTOL, 2.5f,
        0.15f, SFX_WP_BERETTA, 3}, // PISTOL_ASSASSIN
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 240, 5, 0.1, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 3}, // PISTOL_HAND
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 210, 6, 0.15, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 3}, // PISTOL_STARLORD
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 400, 4, 0.1, BULLET_AK, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // SMG_NAILGUN
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 40, 24, 0.7, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_AK, 3}, // SHOTGUN_PLANT
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 100, 5, 0.4, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_RIFLE, 3}, // SNIPER_DRAGUNOV
    {WEAPON_TYPE_PISTOL, FIRE_SINGLE, 120, 4, 0.25, BULLET_PISTOL, 2.5f, 0.15f,
        SFX_WP_BERETTA, 3}, // PISTOL_GRAPLING
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 100, 15, 0.55, BULLET_AK, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // RIFLE_PARINO
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 40, 38, 1.4, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_RIFLE, 3}, // SNIPER_ARTIC
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 18, 0.3, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3}, // MELEE_IRONFIST
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 15, 0.5, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3}, // MELEE_BOOMERANG
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 25, 1.1, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3}, // MELEE_SAURON
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 20, 0.65, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3}, // MELEE_LIGHTSABER
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 35, 35, 0.5, BULLET_AK, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // LASER_PARTY
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 40, 30, 0.65, BULLET_AK, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // BOSS_TURTLE
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 35, 60, 0.5, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3}, // MELEE_RACKET
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 200, 6, 0.6, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_AK, 3}, // SHOTGUN_BOLTACTION
    {WEAPON_TYPE_SHOTGUN, FIRE_SINGLE, 190, 8, 0.45, BULLET_SHOTGUN, 2.5f,
        0.15f, SFX_WP_AK, 3}, // SHOTGUN_SKULL
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 300, 4, 0.3, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3}, // MELEE_GUITAR
    {WEAPON_TYPE_RIFLE, FIRE_SINGLE, 90, 25, 0.75, BULLET_AK, 2.5f, 0.15f,
        SFX_WP_AK, 3}, // BOSS_SNAKE
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 150, 10, 0.25, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3}, // MELEE_BAMBO
    {WEAPON_TYPE_SNIPER, FIRE_SINGLE, 90, 20, 1.2, BULLET_SNIPER, 2.5f, 0.15f,
        SFX_WP_RIFLE, 3}, // SNIPER_BONE_CROSSBOW
    {WEAPON_TYPE_MELEE, FIRE_SINGLE, 100, 15, 0.65, BULLET_MELEE, 2.5f, 0.15f,
        SFX_WP_KNIFE, 3} // MELEE_FISHING_ROD
};

///////////////////////////////////////////////////////////////////////////////
/// \brief destroy bullets when they hit their targets or get out of the
/// circle.
///
/// \param sender       The shooter.
/// \param direction    The vector to design the target.
/// \param weapon       The weapon used by the shooter.
///
///////////////////////////////////////////////////////////////////////////////
void create_bullet(actor_t *sender, v2f_t direction, weapon_enum_t weapon);

///////////////////////////////////////////////////////////////////////////////
/// \brief destroy bullets when they hit their targets or get out of the
/// circle.
///
/// \param bullet       the sprite_sheet of the bullet.
///
///////////////////////////////////////////////////////////////////////////////
void destroy_bullet(bullet_t *bullet);

///////////////////////////////////////////////////////////////////////////////
/// \brief Drawing all the bullets.
///
///
///////////////////////////////////////////////////////////////////////////////
void draw_all_bullets(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Update the state and position of every bullet in the Pool.
///
///////////////////////////////////////////////////////////////////////////////
void update_all_bullets(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Update the state and position of every bullet in the Pool.
///
///////////////////////////////////////////////////////////////////////////////
weapon_enum_t search_weapon(actor_t *act);

///////////////////////////////////////////////////////////////////////////////
/// \brief Update the state and position of every bullet in the Pool.
///
///////////////////////////////////////////////////////////////////////////////

#endif /* !WEAPONS_H_ */
