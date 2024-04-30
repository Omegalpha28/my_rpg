/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

static float rotation(weapon_t *bullet)
{
    float_t my_x = bullet->destination.x - bullet->origin.x;
    float_t my_y = bullet->destination.y - bullet->origin.y;
    float_t rotationDegrees = atan2(my_y, my_x) * (180.f / M_PI);

    return rotationDegrees;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Renders a bullet, updating its position based on its origin,
/// destination, and velocity.
///
/// \param              bullet pointer to bullet structure.
///
///////////////////////////////////////////////////////////////////////////////
static void bullet_render(bullet_t *bullet)
{
    v2f_t direction = {bullet->destination.x - bullet->origin.x,
        bullet->destination.y - bullet->origin.y};
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    sfVector2f position = sfSprite_getPosition(bullet->sprite);
    float vitesse = 5;

    direction = divide2f(direction, (v2f_t){length, length});
    direction = multiply2f(direction, (v2f_t){vitesse, vitesse});
    position = add2f(position, direction);
    sfSprite_setPosition(bullet->sprite, position);
    sfRenderWindow_drawSprite(Win.self, bullet->sprite, NULL);
}

static void weapon_render(weapon_t *weapon)
{
    sfSprite_setOrigin(weapon->sprite, weapon->origin);
    sfSprite_setPosition(weapon->sprite, weapon->position);
    sfSprite_setRotation(weapon->sprite, rotation(weapon));
    if (weapon->destination.x < Player.ref->position.x)
        sfSprite_setScale(weapon->sprite, (v2f_t){1.0, -1.0});
    else
        sfSprite_setScale(weapon->sprite, (v2f_t){1.0, 1.0});
    sfRenderWindow_drawSprite(Win.self, weapon->sprite, NULL);
}

///////////////////////////////////////////////////////////////////////////////
static void update_info_weapon(weapon_t *weapon)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    weapon->position = (v2f_t){Player.ref->position.x, Player.ref->position.y};
    weapon->destination = endpoint2f(weapon->origin, cr, 100.0f);
}

///////////////////////////////////////////////////////////////////////////////
static void weapon_update(void)
{
    if (Weapon_List.weapon == NULL)
        return;
    for (uint_t i = 0; i < Weapon_List.count; i++) {
        if (Weapon_List.weapon[i]->enable) {
            update_info_weapon(Weapon_List.weapon[i]);
            weapon_render(Weapon_List.weapon[i]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void bullet_update(void)
{
    weapon_update();
    if (Bullet_List.array == NULL)
        return;
    for (uint_t i = 0; i < Bullet_List.count; i++) {
        if (Bullet_List.array[i]->destroyed)
            continue;
        bullet_render(Bullet_List.array[i]);
        bullet_collision(Bullet_List.array[i]);
    }
    for (uint_t i = 0; i < Bullet_List.count; i++) {
        if (!Bullet_List.array[i]->destroyed)
            continue;
        remove_bullet(Bullet_List.array[i]);
        i--;
    }
}
