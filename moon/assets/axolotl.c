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
static void init_axolotl(uint_t i, axolotles_t *axo)
{
    axo->grown = AXO_NO;
    axo->maxHealth = AXOLOTL_STATS[i].maxHealth;
    axo->shields = AXOLOTL_STATS[i].shields;
    axo->speed = AXOLOTL_STATS[i].speed;
    axo->disp = false;
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_axolotl(void)
{
    Assets.axolotl = (axolotles_t **)malloc(sizeof(axolotles_t *) * AXO_COUNT);
    if (Assets.axolotl == NULL)
        return (false);
    for (uint_t i = 0; i < AXO_COUNT; i++) {
        Assets.axolotl[i] = (axolotles_t *)malloc(sizeof(axolotles_t));
        Assets.axolotl[i]->name = AXOLOPEDIA_NAMES[i];
        Assets.axolotl[i]->axolotl_egg = add_image(AXOLOPEDIA_EGG[i],
            true, V2U1(1U), AXOLOPEDIA_NAMES[i]);
        Assets.axolotl[i]->axolotl_baby = add_image(AXOLOPEDIA_BABIES[i],
            true, V2U1(1U), AXOLOPEDIA_NAMES[i]);
        Assets.axolotl[i]->axolotl_teen = add_image(AXOLOPEDIA_TEENS[i],
            true, V2U1(1U), AXOLOPEDIA_NAMES[i]);
        Assets.axolotl[i]->axolotl = add_image(AXOLOPEDIA_ADULTS[i],
            true, V2U1(1U), AXOLOPEDIA_NAMES[i]);
        init_axolotl(i, Assets.axolotl[i]);
    }
    Assets.axolotl[AXO_ORIGINAL]->grown = AXO_ADULT;
    Assets.axolotl[AXO_ORIGINAL]->disp = true;
    Assets.axolotlCount = AXO_COUNT;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_all_axolotl(void)
{
    FREE(Assets.axolotl);
}
