/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** ui
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_ui(void)
{
    Assets.ui = (image_t **)malloc(sizeof(image_t *) * UI_ELEMENT_COUNT);
    if (Assets.ui == NULL)
        return (false);
    for (uint_t i = 0; i < UI_ELEMENT_COUNT; i++) {
        Assets.ui[i] = add_image(UI_ELEMENTS_PATHS[i], true, V2U1(1U), "UI");
        if (Assets.ui[i] == NULL)
            return (false);
    }
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets_ui(void)
{
    FREE(Assets.ui);
    Assets.ui = NULL;
    Assets.uiCount = 0;
}
