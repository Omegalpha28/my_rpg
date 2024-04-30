/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_weapon
*/
#include "rpg.h"

static float rotation(weapon_t *weapon)
{
    float_t my_x = weapon->destination.x - weapon->origin.x;
    float_t my_y = weapon->destination.y - weapon->origin.y;
    float_t rotationDegrees = atan2(my_y, my_x) * (180.f / M_PI);

    return rotationDegrees;
}

static sfSprite *init_weapon_sprite(uint_t num, weapon_t *weapon)
{
    sfSprite *weapon_sprite = sfSprite_create();
    recti_t rect = Assets.weapons[num]->mask;
    v2f_t pos = Player.ref->position;
    sfTexture *texture = Assets.weapons[num]->self;

    sfSprite_setTexture(weapon_sprite, texture, sfTrue);
    sfSprite_setTextureRect(weapon_sprite, rect);
    sfSprite_setPosition(weapon_sprite, (v2f_t){pos.x,
        pos.y});
    sfSprite_setOrigin(weapon_sprite, (v2f_t){rect.width / 2,
        rect.height / 2});
    sfSprite_setRotation(weapon_sprite, rotation(weapon));
    return weapon_sprite;
}

static weapon_t *create_weapon(uint_t num)
{
    weapon_t *new = (weapon_t *)malloc(sizeof(weapon_t));
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    new->type = num;
    new->rect = Assets.weapons[num]->mask;
    new->origin = (v2f_t){new->rect.height / 2, new->rect.width / 2};
    new->position = (v2f_t){Player.ref->position.x, Player.ref->position.y};
    new->destination = endpoint2f(new->origin, cr, 100.0f);
    new->sprite = init_weapon_sprite(num, new);
    new->ammos = 0;
    new->damage = 0;
    new->enable = false;
    new->firerate = (float_t){0};
    return (new);

}

static weapon_t *weapon_creation(uint_t num)
{
    weapon_t *new = create_weapon(num);
    if (num == 0)
        new->enable = true;
    shake(2.5f, 0.15f);
    Weapon_List.count++;
    Weapon_List.weapon = REALLOC(Weapon_List.weapon, sizeof(weapon_t *),
        Weapon_List.count);
    Weapon_List.weapon[Weapon_List.count - 1] = new;
    return (new);
}

void init_weapons(void)
{
    for (uint_t e = 0; e < WEAPON_TYPE_COUNT; e++) {
        weapon_creation(e);
    }
}

void remove_weapon(weapon_t *weapon)
{
    weapon_t **tmp = NULL;
    uint_t j = 0;

    if (weapon == NULL)
        return;
    tmp = malloc(sizeof(weapon_t *) * (Weapon_List.count - 1));
    for (uint_t i = 0; i < Weapon_List.count; i++) {
        if (Weapon_List.weapon[i] == weapon)
            continue;
        tmp[j] = Weapon_List.weapon[i];
        j++;
    }
    Weapon_List.count--;
    FREE(Weapon_List.weapon);
    Weapon_List.weapon = tmp;
    FREE(weapon);
}

