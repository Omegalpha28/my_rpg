/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** sfx
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static bool_t add_assets_sfx(uint_t i)
{
    sfx_t *new = (sfx_t *)malloc(sizeof(sfx_t));
    string_t fp = NULL;

    new->soundCount = 0;
    for (uint_t j = 0; j < MAX_SFX_VARIANTS; j++)
        new->sounds[j] = NULL;
    for (uint_t j = 0; SFX_ASSETS[i][j] != NULL; j++) {
        fp = my_strdcat(DIR_ASSETS, "/sfx/", SFX_ASSETS[i][j]);
        new->sounds[j] = sfSoundBuffer_createFromFile(fp);
        FREE(fp);
        if (new->sounds[j] == NULL)
            return (false);
        new->soundCount++;
    }
    Assets.sfxCount++;
    Assets.sfx = REALLOC(Assets.sfx, sizeof(sfx_t *),
        Assets.sfxCount);
    Assets.sfx[Assets.sfxCount - 1] = new;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_sfx(void)
{
    for (uint_t i = 0; i < SFX_COUNT; i++)
        if (!add_assets_sfx(i))
            return (false);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t destroy_assets_sfx(void)
{
    for (uint_t i = 0; i < Assets.sfxCount; i++) {
        for (uint_t j = 0; Assets.sfx[i]->sounds[j]; j++)
            sfSoundBuffer_destroy(Assets.sfx[i]->sounds[j]);
        FREE(Assets.sfx[i]);
    }
    FREE(Assets.sfx);
    Assets.sfx = NULL;
    Assets.sfxCount = 0U;
    return (true);
}
