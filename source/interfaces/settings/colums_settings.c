/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** colums_settings
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

sfColor colums(v2f_t pos, cstring_t str, float scale, int center)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    float str_map = strlen(str) * 16.0f * Win.width / Win.viewWidth * scale;
    float strmap = str_map / strlen(str);

    RETURN(mouse.y > PX_TO_MAPF(V2F1(pos.y + strmap * 2)).y || mouse.y <
        PX_TO_MAPF(V2F1(pos.y - strmap)).y, sfWhite);
    if (center == 1)
        RETURN(mouse.x > PX_TO_MAPF(V2F1(pos.x + strmap * 0.5 + str_map)).x ||
            mouse.x < PX_TO_MAPF(V2F1(pos.x- strmap * 0.5f)).x, sfWhite);
    if (center == 2)
        RETURN(mouse.x > PX_TO_MAPF(V2F1(pos.x + strmap * 0.5 + str_map / 2)).x
            || mouse.x <
            PX_TO_MAPF(V2F1(pos.x - str_map / 2 - strmap * 0.5f)).x, sfWhite);
    if (center == 3)
        RETURN(mouse.x > PX_TO_MAPF(V2F1(pos.x + strmap * 0.5)).x || mouse.x <
            PX_TO_MAPF(V2F1(pos.x - str_map - strmap * 0.5f)).x, sfWhite);
    return (sfColor_fromRGB(243, 199, 77));
}
