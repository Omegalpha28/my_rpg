/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** shoot
*/

///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static bool_t can_shoot(void)
{
    weapon_t wp = WEAPON_STATS[Player.weapon];
    int ammo = Player.mag[(Player.inventor[1] == Player.weapon)];
    ulong_t elsp = (Time.currentTime - Player.shoot_time);

    if (!MPRESSED(Setting.shoot) || DANCE || DASH)
        return (false);
    if (ammo == 0 || (elsp < wp.firerate * 1e3))
        return (false);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static void check_empty_weapon(void)
{
    if (Player.inventor[1] != WEAPON_NO && Player.max_bullet == 0) {
        Player.weapon = Player.inventor[0];
        Player.inventor[1] = WEAPON_NO;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void check_reloading(void)
{
    weapon_t wp = WEAPON_STATS[Player.weapon];
    int magId = (Player.inventor[1] == Player.weapon);
    int ammo = Player.mag[(Player.inventor[1] == Player.weapon)];
    ulong_t elsp = (Time.currentTime - Player.shoot_time);

    Player.reloading = (ammo == 0 && elsp < (wp.reload_time * 1e3));
    if (ammo != 0 || elsp < (wp.reload_time * 1e3))
        return;
    if (magId == 1 && Player.max_bullet < wp.ammoPerMag)
        Player.mag[magId] = Player.max_bullet;
    if (magId == 0 || Player.max_bullet >= wp.ammoPerMag)
        Player.mag[magId] = wp.ammoPerMag;
}

///////////////////////////////////////////////////////////////////////////////
void check_shoot(void)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    check_empty_weapon();
    check_reloading();
    if (!can_shoot())
        return;
    Player.mag[(Player.inventor[1] == Player.weapon)]--;
    if (Player.mag[(Player.inventor[1] == Player.weapon)] == 0)
        sfx(SFX_RELOAD);
    Player.max_bullet -= (Player.weapon == Player.inventor[1]) ? 1 : 0;
    Player.shoot_time = Time.currentTime;
    create_bullet(Player.ref, cr, Player.weapon);
}
