/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** draw bullet_sprite
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void draw_bullet_trace(bullet_t *bullet)
{
    sfVertexArray *va = sfVertexArray_create();
    sfVertex v;

    v.color = sfBlue;
    v.position = bullet->origin;
    sfVertexArray_append(va, v);
    v.position = bullet->destination;
    sfVertexArray_append(va, v);
    sfVertexArray_setPrimitiveType(va, sfLines);
    sfRenderWindow_drawVertexArray(Win.self, va, NULL);
    sfVertexArray_destroy(va);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_bullet(bullet_t *bullet)
{
    image_t *img = bullet->img;
    ulong_t ems = (Time.currentTime - bullet->startAt);
    recti_t mask = img->mask;
    uint_t frame = (ems / VIDEO_FRAMERATE) % (img->grid.x * img->grid.y);

    mask.left = (frame % img->grid.x) * mask.width;
    mask.top = (frame / img->grid.x) * mask.height;
    sfSprite_setTexture(bullet->sprite, img->self, false);
    sfSprite_setTextureRect(bullet->sprite, mask);
    sfSprite_setOrigin(bullet->sprite, V2F(mask.width / 2.0f, mask.height /
        2.0f));
    sfSprite_setPosition(bullet->sprite, bullet->position);
    sfRenderWindow_drawSprite(Win.self, bullet->sprite, NULL);
    if (Engine.debugMode)
        draw_bullet_trace(bullet);
    if (frame == (img->grid.x * img->grid.y - 1) &&
        bullet->state == BULLET_STATE_IMPACT)
        bullet->state = BULLET_STATE_DESTROYED;
}

///////////////////////////////////////////////////////////////////////////////
void draw_all_bullets(void)
{
    for (uint_t i = 0; i < Pool.bulletCount; i++)
        draw_bullet(Pool.bullets[i]);
}
