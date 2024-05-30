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
            ammoPerMag, 0, WEAPON_STATS[obj->data[0]].ammoPerMag * 3);
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
        Player.max_bullet = WEAPON_STATS[Player.weapon].ammoPerMag;
    } else {
        Player.mag[1] = obj->data[1];
        Player.max_bullet = obj->data[2];
    }
    sfx(SFX_PICK_WEAPON);
    destroy_interactable(obj);
    Player.lastAction = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
static int get_random_baby(void)
{
    int rdx = rand() % AXO_COUNT;

    while (Assets.axolotl[rdx]->grown != AXO_NO)
        rdx = rand() % AXO_COUNT;
    return (rdx);
}

///////////////////////////////////////////////////////////////////////////////
void openchest(interactable_t *obj)
{
    v2f_t pos = add2f(obj->position, V2F(rand() % 50, rand() % 50));
    actor_set_anim(obj->actor, "open");
    sfx(SFX_CHEST_OPEN);
    if (obj->data[0] == 0)
        spawn_interactable(INTERACTABLE_WEAPON, pos, rand() %
            WEAPON_MELEE_FISHING_ROD, &pickup);
    if (obj->data[0] == 1)
        return;
    if (obj->data[0] == 2)
        spawn_interactable(INTERACTABLE_EGG, pos, get_random_baby(),
            &pickupchild);
    if (obj->data[0] == 3) {
        for (uint_t i = 0; i < 5; i++)
            spawn_interactable(INTERACTABLE_CURRENCY, add2f(obj->position,
                V2F(rand() % 50, rand() % 50)), CURRENCY_COOKIE, &pickupitem);
    }
    Player.lastAction = Time.currentTime;
}

///////////////////////////////////////////////////////////////////////////////
void pickupitem(interactable_t *obj)
{
    sfx(SFX_PICKUP_ITEM);
    destroy_interactable(obj);
}

///////////////////////////////////////////////////////////////////////////////
void pickupchild(interactable_t *obj)
{
    effect_t *eff = effect("egg_to_baby", obj->position, false);

    sfx(SFX_EVOLVE);
    eff->framerate = FRAME_PER_MS(32);
    Assets.axolotl[obj->data[0]]->grown = AXO_BABY;
    destroy_interactable(obj);
}
