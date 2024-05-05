/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** bullets
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static v2u_t get_bullet_grid(cstring_t str)
{
    string_t base = my_basename(str);
    warray_t split = my_strsplit(base, '-');
    warray_t coord = NULL;
    v2u_t grid = V2U1(0U);

    if (split && split[1] && my_countchar(split[1], 'x') == 1) {
        coord = my_strsplit(split[1], 'x');
        grid.x = (uint_t)atoi(coord[0]);
        grid.y = (uint_t)atoi(coord[1]);
        my_watroy(coord);
    }
    my_watroy(split);
    return (grid);
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_bullets(void)
{
    Assets.bullets = (image_t **)malloc(sizeof(image_t *) * T_BULLET_COUNT);
    if (Assets.bullets == NULL)
        return (false);
    for (uint_t i = 0; i < T_BULLET_COUNT; i++) {
        Assets.bullets[i] = add_image(TEXT_BULLETS[i], true,
            get_bullet_grid(TEXT_BULLETS[i]), "BULLETS");
        if (Assets.bullets[i] == NULL)
            return (false);
    }
    Assets.bulletCount = T_BULLET_COUNT;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets_bullets(void)
{
    FREE(Assets.bullets);
    Assets.bullets = NULL;
    Assets.bulletCount = 0;
}
