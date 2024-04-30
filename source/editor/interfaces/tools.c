/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** tools
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static sfColor get_color_base_total(uint_t total)
{
    sfColor color = RGB(0, 200, 0);

    if (total > 100)
        color = RGB(0, 175, 0);
    if (total > 200)
        color = RGB(200, 200, 0);
    if (total > 300)
        color = RGB(155, 155, 0);
    if (total > 500)
        color = RGB(200, 0, 0);
    if (total > 750)
        color = RGB(155, 0, 0);
    return (color);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_memory_usage(void)
{
    float fact = FACTORS(V2F1(20.0f)).x;
    uint_t total = Editor.fCount + Editor.bCount;
    ulong_t bytes = (total * 16) + 6 + strlen(Editor.zone->name);
    char usage[76];

    if (bytes < 1e3)
        snprintf(usage, 76, "%.0f b - %u props", bytes / 1.0f, total);
    if (bytes > 1e3 && bytes < 1e6)
        snprintf(usage, 76, "%.3f Kb - %u props", bytes / 1000.0f, total);
    if (bytes > 1e6)
        snprintf(usage, 76, "%.3f Mb - %u props", bytes / 1000000.0f, total);
    draw_text("Memory usage", PX_TO_MAPF(V2F(255.0f, EDITOR_PANEL_H + 11.0f)),
        fact, WHITE);
    draw_text(usage, PX_TO_MAPF(V2F(455.0f, EDITOR_PANEL_H + 11.0f)),
        fact, get_color_base_total(total));
}

///////////////////////////////////////////////////////////////////////////////
static void draw_framerate(void)
{
    float fact = FACTORS(V2F1(20.0f)).x;
    float fps = 1000.0f / Time.deltaTime;
    char text[12];

    snprintf(text, 12, "%.0f", roundf(fps));
    draw_text("Framerate", PX_TO_MAPF(V2F(855.0f, EDITOR_PANEL_H + 11.0f)),
        fact, WHITE);
    draw_text(text, PX_TO_MAPF(V2F(1010.0f, EDITOR_PANEL_H + 11.0f)),
        fact, RGB(200, 0, 200));
}

///////////////////////////////////////////////////////////////////////////////
static void draw_active_layer(void)
{
    float fact = FACTORS(V2F1(20.0f)).x;

    draw_text("Layer", PX_TO_MAPF(V2F(1320.0f, EDITOR_PANEL_H + 11.0f)),
        fact, WHITE);
    draw_text(Editor.layer == EDITOR_LAYER_BACKGROUND ? "Background" :
        "Foreground", PX_TO_MAPF(V2F(1420.0f, EDITOR_PANEL_H + 11.0f)),
        fact, RGB(200, 200, 0));
}

///////////////////////////////////////////////////////////////////////////////
void draw_editor_toolbar(void)
{
    draw_rect(V2F(Win.width, EDITOR_PANEL_H), V2F(0.0f, EDITOR_PANEL_H),
        EDITOR_WIDGET);
    draw_memory_usage();
    draw_framerate();
    draw_active_layer();
}
