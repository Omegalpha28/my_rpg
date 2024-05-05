/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy
*/
#include "rpg.h"

void remove_bullet(bullet_t *bullet)
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
    FREE(bullet);
}
