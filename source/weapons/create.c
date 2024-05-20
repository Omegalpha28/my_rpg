/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** bullet_animation
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void init_new_bullet(bullet_t *new, actor_t *sender, v2f_t direction,
    weapon_t wp)
{
    v2f_t origin = add2f(sender->position, V2F(0.0f, 8.0f));

    new->origin = endpoint2f(origin, direction, 25.0f);
    new->destination = endpoint2f(origin, direction,
        BULLET_STATS[wp.bulletType].range + 25.0f);
    new->position = new->origin;
    new->sender = sender;
    new->startAt = Time.currentTime;
    new->state = BULLET_STATE_FLYING;
    if (wp.bulletType == BULLET_KATANA || wp.bulletType == BULLET_MOTORBLADE ||
        wp.bulletType == BULLET_MELEE)
        new->state = BULLET_STATE_IMPACT;
    new->sprite = sfSprite_create();
    new->img = Assets.bullets[BULLET_STATS[wp.bulletType].base];
    new->rotation = atan2(new->destination.y - new->origin.y,
        new->destination.x - new->origin.x) * (180.0f / M_PI);
    sfSprite_setRotation(new->sprite, new->rotation);
}

///////////////////////////////////////////////////////////////////////////////
void create_bullet(actor_t *sender, v2f_t direction, weapon_enum_t weapon)
{
    bullet_t *new = malloc(sizeof(bullet_t));

    new->weapon = weapon;
    init_new_bullet(new, sender, direction, WEAPON_STATS[weapon]);
    Pool.bulletCount++;
    Pool.bullets = REALLOC(Pool.bullets, sizeof(bullet_t *),
        Pool.bulletCount);
    Pool.bullets[Pool.bulletCount - 1] = new;
    sfx(WEAPON_STATS[weapon].sound);
    sfSound_setAttenuation(sfx(SFX_KICK), 50);
    if (sender != Player.ref)
        return;
    shake(WEAPON_STATS[weapon].shakingIntensity,
        WEAPON_STATS[weapon].shakingDuration);
}

///////////////////////////////////////////////////////////////////////////////
weapon_enum_t search_weapon(actor_t *act)
{
    for (int i = 0; i < Entities.count; i++) {
        if (act == Entities.array[i]->actor && act != Player.ref) {
            return (Entities.array[i]->weapon);
        }
    }
    return (0);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_bullet(bullet_t *bullet)
{
    bullet_t **tmp = NULL;
    uint_t j = 0;

    if (bullet == NULL)
        return;
    tmp = malloc(sizeof(bullet_t *) * (Pool.bulletCount - 1));
    for (uint_t i = 0; i < Pool.bulletCount; i++) {
        if (Pool.bullets[i] == bullet)
            continue;
        tmp[j] = Pool.bullets[i];
        j++;
    }
    Pool.bulletCount--;
    FREE(Pool.bullets);
    Pool.bullets = tmp;
    if (bullet->sprite != NULL)
        sfSprite_destroy(bullet->sprite);
    FREE(bullet);
}
