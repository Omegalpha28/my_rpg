/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** axolotl
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_axolotl(void)
{
    Assets.axolotl = (axolotles_t **)malloc(sizeof(axolotles_t *) * AXO_COUNT);
    if (Assets.axolotl == NULL)
        return (false);
    for (uint_t i = 0; i < AXO_COUNT; i++) {
        Assets.axolotl[i] = (axolotles_t *)malloc(sizeof(axolotles_t));
        Assets.axolotl[i]->is_egg = false;
        Assets.axolotl[i]->is_baby = false;
        Assets.axolotl[i]->is_teen = false;
        Assets.axolotl[i]->is_adult = false;
    }
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_all_axolotl(void)
{
    FREE(Assets.axolotl);
    Assets.axolotl = NULL;
    Assets.axolotlCount = 0;
}
