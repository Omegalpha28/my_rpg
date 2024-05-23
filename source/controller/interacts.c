/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** interacts
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void release_old_weapon(interactable_t *obj)
{
    interactable_t *new = NULL;
    bool_t same = (Player.inventor[1] == obj->data[0]);

    if (same) {
        obj->data[1] = Player.mag[1];
        obj->data[2] = clamp(Player.max_bullet + WEAPON_STATS[obj->data[0]].
            ammoPerMag * 5, 0, WEAPON_STATS[obj->data[0]].ammoPerMag * 8);
    }
    if (Player.inventor[1] != WEAPON_NO && !same) {
        sfx(SFX_WEAPON_SWAP_WHOOSH);
        new = spawn_interactable(INTERACTABLE_WEAPON, Player.ref->position,
            Player.inventor[1], &pickup);
        new->data[1] = Player.mag[1];
        new->data[2] = Player.max_bullet;
    }
}

///////////////////////////////////////////////////////////////////////////////
void pickup(interactable_t *obj)
{
    release_old_weapon(obj);
    Player.inventor[1] = (weapon_enum_t)obj->data[0];
    Player.weapon = Player.inventor[1];
    if (obj->data[1] == -1) {
        Player.mag[1] = WEAPON_STATS[Player.weapon].ammoPerMag;
        Player.max_bullet = WEAPON_STATS[Player.weapon].ammoPerMag * 5;
    } else {
        Player.mag[1] = obj->data[1];
        Player.max_bullet = obj->data[2];
    }
    sfx(SFX_PICK_WEAPON);
    destroy_interactable(obj);
    Player.lastAction = Time.currentTime;
}
