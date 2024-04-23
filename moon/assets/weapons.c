/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** weapons
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static int my_sort_strcmp(const void *a, const void *b)
{
    return (strcmp(*(cstring_t *)a, *(cstring_t *)b));
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_weapons(void)
{
    warray_t ctn = my_dircontent(DIR_WEAPONS);

    qsort(ctn, my_walen(ctn), sizeof(ctn[0]), my_sort_strcmp);
    Assets.weapons = (image_t **)malloc(sizeof(image_t *) * WEAPON_TYPE_COUNT);
    for (uint_t i = 0; ctn[i]; i++) {
        if (my_isdir(ctn[i]) == true)
            continue;
        if (Assets.weaponCount == WEAPON_TYPE_COUNT)
            return (my_error(ERR_TO_MANY_WEAPON));
        Assets.weaponCount++;
        Assets.weapons[i] = add_image(ctn[i], true, V2U(WEAPON_GRID_X,
            WEAPON_GRID_Y), "WEAPONS");
    }
    if (Assets.weaponCount != WEAPON_TYPE_COUNT)
        return (my_error(ERR_TO_FEW_WEAPON));
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets_weapons(void)
{
    FREE(Assets.weapons);
    return;
}
