/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** debug
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void print_debug_pools(float scale, sfColor clr)
{
    char buff[128];

    draw_text("Pools", PX_TO_MAPF(V2F(10.0f, 160.0f)), scale, clr);
    snprintf(buff, 128, "Sounds: %u", Pool.soundCount);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 190.0f)), scale, sfWhite);
    snprintf(buff, 128, "Actors: %u", Pool.actorCount);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 220.0f)), scale, sfWhite);
    snprintf(buff, 128, "Props: %u", Pool.propCount);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 250.0f)), scale, sfWhite);
    snprintf(buff, 128, "Drawn props: %u", Engine.debug.propDrawn);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 280.0f)), scale, sfWhite);
    snprintf(buff, 128, "Bullets: %u", Pool.bulletCount);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 310.0f)), scale, sfWhite);
    snprintf(buff, 128, "Effects: %u", Pool.effectCount);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 340.0f)), scale, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
static void print_debug_level(float scale, sfColor clr)
{
    char buff[128];

    draw_text("Level", PX_TO_MAPF(V2F(10.0f, 400.0f)), scale, clr);
    snprintf(buff, 128, "Level: %u", Engine.level);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 430.0f)), scale, sfWhite);
    snprintf(buff, 128, "Zone: %s", Editor.zone->name);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 460.0f)), scale, sfWhite);
    snprintf(buff, 128, "Foreground: %u props", Editor.fCount);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 490.0f)), scale, sfWhite);
    snprintf(buff, 128, "Background: %u props", Editor.bCount);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 520.0f)), scale, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
static void print_debug_window(float scale, sfColor clr)
{
    char buff[128];

    draw_text("Window", PX_TO_MAPF(V2F(10.0f, 10.0f)), scale, clr);
    snprintf(buff, 128, "Framerate: %u", (uint_t)(1000 / Time.deltaTime) + 1);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 40.0f)), scale, sfWhite);
    snprintf(buff, 128, "Resolution: %ux%u", Win.width, Win.height);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 70.0f)), scale, sfWhite);
    if (Win.mode == WIN_FULLSCREEN)
        snprintf(buff, 128, "Mode: Fullscreen");
    if (Win.mode == WIN_WINDOWED)
        snprintf(buff, 128, "Mode: Windowed");
    if (Win.mode == WIN_BORDERLESS)
        snprintf(buff, 128, "Mode: Borderless");
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 100.0f)), scale, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
static void print_debug_weapon(float scale, sfColor clr)
{
    char buff[128];
    weapon_t wp = WEAPON_STATS[Player.weapon];

    draw_text("Weapon", PX_TO_MAPF(V2F(10.0f, 580.0f)), scale, clr);
    snprintf(buff, 128, "Weapon: %d", Player.weapon);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 610.0f)), scale, sfWhite);
    snprintf(buff, 128, "Damage: %d", wp.damage);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 640.0f)), scale, sfWhite);
    snprintf(buff, 128, "Firerate: %.2f", wp.firerate);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 670.0f)), scale, sfWhite);
    snprintf(buff, 128, "Range: %.2f", BULLET_STATS[wp.bulletType].range);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 700.0f)), scale, sfWhite);
    snprintf(buff, 128, "Speed: %.2f", BULLET_STATS[wp.bulletType].speed);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 730.0f)), scale, sfWhite);
    snprintf(buff, 128, "Ammos: %u", wp.ammoPerMag);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 760.0f)), scale, sfWhite);
    snprintf(buff, 128, "Shaking duration: %.2f", wp.shakingDuration);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 790.0f)), scale, sfWhite);
    snprintf(buff, 128, "Shaking intensity: %.2f", wp.shakingIntensity);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 820.0f)), scale, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
static void print_debug_coordinate(float scale, sfColor clr)
{
    char buff[128];
    v2f_t cur = PX_TO_MAP(sfMouse_getPositionRenderWindow(Win.self));

    draw_text("Player", PX_TO_MAPF(V2F(10.0f, 880.0f)), scale, clr);
    snprintf(buff, 128, "Coordinate: %.2f %.2f\n", Player.ref->position.x,
        Player.ref->position.y);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 910.0f)), scale, sfWhite);
    snprintf(buff, 128, "Dashing: %s\n", DASH ? "True" : "False");
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 940.0f)), scale, sfWhite);
    snprintf(buff, 128, "Dancing: %s\n", DANCE ? "True" : "False");
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 970.0f)), scale, sfWhite);
    snprintf(buff, 128, "Direction: %s\n", Player.ref->scale.x == -1.0f ?
        "Left" : "Right");
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 1000.0f)), scale, sfWhite);
    snprintf(buff, 128, "Cursor: %.0f %.0f\n", cur.x, cur.y);
    draw_text(buff, PX_TO_MAPF(V2F(10.0f, 1030.0f)), scale, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
void print_debug_information(void)
{
    float scale = FACTORS(V2F1(20.0f)).x;
    sfColor clr = RGB(243, 199, 77);

    if (!Engine.debugMode)
        return;
    print_debug_window(scale, clr);
    print_debug_pools(scale, clr);
    print_debug_level(scale, clr);
    print_debug_weapon(scale, clr);
    print_debug_coordinate(scale, clr);
}
