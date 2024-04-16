/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy bullets
*/
#include "rpg.h"

void remove_bullet(bullet_t *bullet)
{
    bullet_t **tmp = NULL;
    uint_t j = 0;

    if (bullet == NULL)
        return;
    tmp = malloc(sizeof(bullet_t *) * (Bullet_List.count - 1));
    for (uint_t i = 0; i < Bullet_List.count - 1; i++) {
        if (Bullet_List.array[i] == bullet)
            continue;
        tmp[j] = Bullet_List.array[i];
        j++;
    }
    Bullet_List.count--;
    FREE(Bullet_List.array);
    Bullet_List.array = tmp;
    FREE(bullet);
}
