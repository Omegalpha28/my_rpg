/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** context
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
context_t CONTEXTS[CONTEXT_COUNT] = {
    {
        "Return", false, {
            {"Zone selection", NULL, false, NULL},
            {"Main menu", NULL, false, NULL}
        }, 2
    },
    {
        "File", false, {
            {"Open level", NULL, false, "CTRL O"},
            {"Save level", NULL, false, "CTRL S"},
            {"Change zone", NULL, false, NULL}
        }, 3
    },
    {
        "Edit", false, {
            {"Copy", &editor_copy, false, "CTRL C"},
            {"Cut", &editor_cut, false, "CTRL X"},
            {"Paste", &editor_paste, false, "CTRL V"},
            {"Duplicate", &editor_duplicate, false, "CTRL D"},
            {"Delete", &editor_delete, false, "SUPPR"},
            {"Clear", NULL, false, NULL},
            {"Flip", NULL, false, NULL}
        }, 7
    },
    {
        "Select", false, {
            {"All", NULL, false, "CTRL A"},
            {"Deselect", NULL, false, NULL}
        }, 2
    },
    {
        "View", false, {
            {"Zoom in", NULL, false, NULL},
            {"Zoom out", NULL, false, NULL},
            {"To origin", NULL, false, "O "}
        }, 3
    },
    {
        "Help", false, {
            {"Shortcuts", NULL, false, "CTRL H"},
            {"About", NULL, false, NULL}
        }, 2
    }
};

///////////////////////////////////////////////////////////////////////////////
static void draw_context_item(v2f_t pos, uint_t ci, uint_t i, float fact)
{
    cstring_t sub = CONTEXTS[ci].items[i].subText;
    ulong_t len = sub ? strlen(sub) : 0;
    v2f_t bPos = V2F(pos.x, pos.y + 42.0f * i + 32.0f);
    bool_t hover = cursor_inbound(bPos, V2F(300.0f, 42.0f));
    sfColor clr = hover && !CONTEXTS[ci].items[i].disabled ? RGB(52, 130, 246)
        : RGB(225, 225, 225);

    draw_rect(V2F(300.0f, 42.0f), bPos, clr);
    draw_text(CONTEXTS[ci].items[i].text, PX_TO_MAPF(add2f(pos,
        V2F(10.0f, 43.0f + (42.0f * i)))), fact, CONTEXTS[ci].items[i].disabled
        ? RGBA(255, 255, 255, 100) : sfWhite);
    if (sub)
        draw_text(sub, PX_TO_MAPF(add2f(pos, V2F(295.0f - (len * 16.0f),
            43.0f + (42.0f * i)))), fact, RGB(200, 200, 200));
    if (hover) {
        Editor.hover = true;
        if (CONTEXTS[ci].items[i].onClick != NULL && MPRESSED(sfMouseLeft))
            CONTEXTS[ci].items[i].onClick();
        Editor.released = false;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void check_context_opening(bool_t hover, uint_t ci)
{
    bool_t press = sfMouse_isButtonPressed(sfMouseLeft);

    if (!hover)
        return;
    if (press && Editor.released) {
        for (uint_t j = 0; j < CONTEXT_COUNT; j++)
            CONTEXTS[j].expand = j == ci ? CONTEXTS[j].expand : false;
        CONTEXTS[ci].expand = !CONTEXTS[ci].expand;
        Editor.released = false;
    }
    for (uint_t j = 0; !(CONTEXTS[ci].expand) && j < CONTEXT_COUNT; j++) {
        if (j == ci || !CONTEXTS[j].expand)
            continue;
        CONTEXTS[j].expand = false;
        CONTEXTS[ci].expand = true;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void draw_context_buttons(cstring_t str, v2f_t pos, uint_t ci)
{
    float fact = FACTORS(V2F1(20.0f)).x;
    ulong_t len = strlen(str);
    v2f_t size = V2F((16.0f * len) + 20.0f, 32.0f);
    bool_t hover = cursor_inbound(pos, size);

    draw_rect(size, pos, hover ? EDITOR_HOVER : EDITOR_BUTTON);
    check_context_opening(hover, ci);
    draw_text(str, PX_TO_MAPF(add2f(pos, V2F(10.0f, 6.0f))), fact, sfWhite);
    if (CONTEXTS[ci].expand == false)
        return;
    for (uint_t i = 0; i < CONTEXTS[ci].itemCount; i++)
        draw_context_item(pos, ci, i, fact);
}

///////////////////////////////////////////////////////////////////////////////
static void check_context_disability(void)
{
    CONTEXTS[1].items[1].disabled = (Editor.bCount + Editor.fCount == 0U);
    CONTEXTS[2].items[0].disabled = (Editor.focus == NULL);
    CONTEXTS[2].items[1].disabled = (Editor.focus == NULL);
    CONTEXTS[2].items[2].disabled = (Editor.copy == NULL);
    CONTEXTS[2].items[3].disabled = (Editor.focus == NULL);
    CONTEXTS[2].items[4].disabled = (Editor.focus == NULL);
    CONTEXTS[2].items[6].disabled = (Editor.focus == NULL);
    CONTEXTS[3].items[1].disabled = (Editor.focus == NULL);
}

///////////////////////////////////////////////////////////////////////////////
void draw_editor_context_menu(void)
{
    float offsetX = 0.0f;

    Editor.hover = false;
    check_context_disability();
    draw_rect(V2F(Win.width, EDITOR_PANEL_H), V2F1(0.0f), EDITOR_WIDGET);
    for (uint_t i = 0; i < CONTEXT_COUNT; i++) {
        draw_context_buttons(CONTEXTS[i].text, V2F(5.0f + offsetX, 5.0f), i);
        offsetX += (16.0f * strlen(CONTEXTS[i].text)) + 30.0f;
    }
}
