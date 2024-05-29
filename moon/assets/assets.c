/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** assets
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
struct assets_s Assets = {
    NULL, 0,
    NULL, 0,
    NULL, 0,
    NULL, 0,
    NULL, 0,
    NULL,
    NULL, 0,
    NULL, 0,
    NULL, 0,
    NULL, 0,
    NULL
};

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets(void)
{
    if (!init_assets_creatures() ||
        !init_assets_musics() ||
        !init_assets_zones() ||
        !init_assets_vfx() ||
        !init_assets_weapons() ||
        !init_assets_ui() ||
        !init_assets_bullets() ||
        !init_assets_sfx() ||
        !init_assets_axolotl() ||
        !init_assets_babies())
        return (false);
    sort_creatures();
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets(void)
{
    destroy_assets_musics();
    destroy_assets_zones();
    destroy_assets_vfx();
    destroy_assets_ui();
    destroy_assets_bullets();
    destroy_assets_sfx();
    destroy_all_axolotl();
    destroy_all_images();
    destroy_all_babies();
}
