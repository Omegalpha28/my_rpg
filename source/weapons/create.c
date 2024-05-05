/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** bullet_animation
*/
#include "rpg.h"

static float rotation(bullet_t *bullet)
{
    float_t my_x = bullet->destination.x - bullet->origin.x;
    float_t my_y = bullet->destination.y - bullet->origin.y;
    float_t rotationDegrees = atan2(my_y, my_x) * (180.f / M_PI);

    return rotationDegrees;
}

static sfSprite *create_asset_sprite(uint_t bullet_asset, uint_t sprite_state,
    bullet_t *bullet)
{
    recti_t rect =
        Assets.bullets[BULLET_STATS[bullet_asset].base + sprite_state]->mask;
    sfSprite *bullet_sprite = sfSprite_create();
    sfTexture *texture =
        Assets.bullets[BULLET_STATS[bullet_asset].base + sprite_state]->self;

    sfSprite_setTexture(bullet_sprite, texture, sfTrue);
    sfSprite_setTextureRect(bullet_sprite, rect);
    sfSprite_setScale(bullet_sprite, (v2f_t){0.7f, 0.7f});
    sfSprite_setOrigin(bullet_sprite, V2F1(rect.width / 2.0f));
    sfSprite_setPosition(bullet_sprite, (v2f_t){bullet->position.x,
        bullet->position.y + 5});
    sfSprite_setOrigin(bullet_sprite, V2F(rect.width / 2, rect.height / 2));
    sfSprite_setRotation(bullet_sprite, rotation(bullet));
    return bullet_sprite;
}

static sfCircleShape *create_circle(uint_t bullet_asset, actor_t *sender)
{
    sfCircleShape *circle = sfCircleShape_create();
    sfVector2f origin = sender->position;
    float range = BULLET_STATS[bullet_asset].range;

    sfCircleShape_setRadius(circle, range);
    origin = (sfVector2f){sfCircleShape_getRadius(circle),
        sfCircleShape_getRadius(circle)};
    sfCircleShape_setOutlineThickness(circle, 2.0f);
    sfCircleShape_setOutlineColor(circle, sfRed);
    sfCircleShape_setFillColor(circle, sfTransparent);
    sfCircleShape_setPosition(circle,
        (sfVector2f){sender->position.x, sender->position.y});
    sfCircleShape_setOrigin(circle, origin);
    return circle;
}

static bullet_t *init_bullet(v2f_t destination, actor_t *sender,
    uint_t bullet_asset, weapon_enum_t weapon)
{
    bullet_t *bullet = malloc(sizeof(bullet_t));

    bullet->radius = BULLET_STATS[bullet_asset].range;
    bullet->animation = 1;
    bullet->speed = BULLET_STATS[bullet_asset].speed;
    bullet->base_visisble = true;
    bullet->destroyed = false;
    bullet->impact_player_visisble = false;
    bullet->impact_wall_visisble = false;
    bullet->bullet_asset = bullet_asset;
    bullet->weapon_asset = weapon;
    bullet->area = create_circle(bullet_asset, sender);
    bullet->destroyed = false;
    bullet->origin = (v2f_t){sender->position.x, sender->position.y};
    bullet->destination = destination;
    bullet->position = sender->position;
    return (bullet);
}

void create_bullet(actor_t *sender, v2f_t destination, weapon_enum_t weapon)
{
    uint_t bullet_asset = WEAPON_STATS[weapon].bulletType;
    bullet_t *bullet = malloc(sizeof(bullet));

    if (WEAPON_STATS[weapon].type == WEAPON_TYPE_MELEE)
        return;
    bullet = init_bullet(destination, sender, bullet_asset, weapon);
    bullet->sender = (sender == Player.ref) ? 0 : 1;
    bullet->base = create_asset_sprite(bullet_asset, 0, bullet);
    bullet->impactWall = create_asset_sprite(bullet_asset, 1, bullet);
    bullet->impactEnemy = create_asset_sprite(bullet_asset, 2, bullet);
    bullet->disappear = create_asset_sprite(bullet_asset, 3, bullet);
    shake(2.5f, 0.15f);
    Pool.bulletCount++;
    Pool.bullets = REALLOC(Pool.bullets, sizeof(bullet_t *),
        Pool.bulletCount);
    Pool.bullets[Pool.bulletCount - 1] = bullet;
}
