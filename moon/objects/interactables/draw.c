/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** draw
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static v2f_t get_interactable_position(interactable_t *obj)
{
    float offsetY = sin((float)(Time.currentTime) / 350.0f);

    if (obj->type == INTERACTABLE_CURRENCY || obj->type == INTERACTABLE_WEAPON)
        return (add2f(obj->position, V2F(0.0f, offsetY)));
    return (obj->position);
}

///////////////////////////////////////////////////////////////////////////////
static recti_t get_interactable_mask(interactable_t *obj)
{
    if (obj->type == INTERACTABLE_WEAPON)
        return ((recti_t){obj->data[0] * 42, 24, 42, 24});
    return (obj->img->mask);
}

///////////////////////////////////////////////////////////////////////////////
void draw_interactable(interactable_t *obj)
{
    v2f_t position = get_interactable_position(obj);
    recti_t mask = get_interactable_mask(obj);

    sfSprite_setTexture(obj->sprite, obj->img->self, true);
    sfSprite_setTextureRect(obj->sprite, mask);
    sfSprite_setOrigin(obj->sprite, V2F(mask.width / 2.0f, mask.height /
        2.0f));
    sfSprite_setPosition(obj->sprite, position);
    sfRenderWindow_drawSprite(Win.self, obj->sprite, NULL);
}
