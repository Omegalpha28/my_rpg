/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** vfx
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static vfx_t *create_assets_vfx(warray_t wa)
{
    vfx_t *vfx = (vfx_t *)malloc(sizeof(vfx_t));
    warray_t arr = my_strsplit(wa[1], 'x');

    vfx->name = my_strdup(wa[0]);
    vfx->grid.x = (uint_t)my_atoi(arr[0]);
    vfx->grid.y = (uint_t)my_atoi(arr[1]);
    my_watroy(arr);
    arr = my_strsplit(wa[2], 'x');
    vfx->startingFrame = (uint_t)my_atoi(arr[0]);
    vfx->endingFrame = (uint_t)my_atoi(arr[1]);
    my_watroy(arr);
    vfx->looped = my_atob(wa[3]);
    vfx->background = my_atob(wa[4]);
    return (vfx);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t add_assets_vfx(string_t path)
{
    vfx_t *vfx = NULL;
    string_t name = my_strndup(my_basename(path), my_strlen(my_basename(path))
        - my_strlen(my_extname(my_basename(path))) - 1);
    warray_t wa = my_strsplit(my_basename(name), '-');

    FREE(name);
    if (!wa || my_walen(wa) != 5 || !my_iscoord(wa[1]) || !my_iscoord(wa[2]) ||
        !my_isbool(wa[3]) || !my_isbool(wa[4])) {
        my_watroy(wa);
        return (my_error(ERR_VFX_SYNTAX));
    }
    vfx = create_assets_vfx(wa);
    vfx->self = add_image(path, true, vfx->grid, vfx->name);
    Assets.vfxCount++;
    Assets.vfx = REALLOC(Assets.vfx, sizeof(vfx_t *), Assets.vfxCount);
    Assets.vfx[Assets.vfxCount - 1] = vfx;
    my_watroy(wa);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_vfx(void)
{
    warray_t content = my_dircontent(DIR_VFX);
    bool_t success = true;

    if (content == NULL)
        return (my_error(ERR_FD_MUSICS));
    for (uint_t i = 0; success && content[i]; i++) {
        if (my_isdir(content[i]))
            continue;
        success = add_assets_vfx(content[i]);
    }
    my_watroy(content);
    return (success);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets_vfx(void)
{
    for (uint_t i = 0; i < Assets.vfxCount; i++) {
        FREE(Assets.vfx[i]->name);
        FREE(Assets.vfx[i]);
    }
    FREE(Assets.vfx);
    Assets.vfx = NULL;
    Assets.vfxCount = 0;
}
