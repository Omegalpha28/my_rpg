/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** browser
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void draw_editor_browser_category(uint_t i, float offsetY)
{
    v2f_t pos = V2F(15.0f, 84.0f + i * 52.0f + offsetY);
    v2f_t size = V2F(220.0f, EDITOR_PANEL_H);
    sfColor color = cursor_inbound(pos, size) ? RGB(200, 0, 0) : sfRed;

    draw_rect(size, pos, color);
}

///////////////////////////////////////////////////////////////////////////////
static void set_category_items_sprite(uint_t i, uint_t j, sfSprite *sprt)
{
    category_t *cat = Editor.zone->categories[i];
    recti_t mask = cat->sheets[j]->image->mask;
    float maxDist = mask.width > mask.height ? mask.width : mask.height;
    float scale = 80.0f / maxDist;
    v2f_t size = V2F(mask.width * scale, mask.height * scale);
    v2f_t fact = multiply2f(FACTORS(size), V2F(scale, scale));

    sfSprite_setTexture(sprt, cat->sheets[j]->image->self, false);
    sfSprite_setTextureRect(sprt, mask);
    sfSprite_setOrigin(sprt, V2F(mask.width / 2.0f, mask.height / 2.0f));
    sfSprite_setScale(sprt, fact);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_editor_browser_category_items(uint_t i, float *offsetY,
    sfSprite *sprt)
{
    category_t *cat = Editor.zone->categories[i];
    v2f_t pos = V2F1(0.0f);
    v2f_t size = V2F(100.0f, 100.0f);

    for (uint_t j = 0; j < cat->sheetCount; j++) {
        pos.x = 15.0f + (j % 2) * 120.0f;
        pos.y = 89.0f + (i + 1) * 52.0f + (j / 2) * 110.0f + (*offsetY);
        draw_rect(size, pos, cursor_inbound(pos, size) ? EDITOR_HOVER :
            EDITOR_BUTTON);
        set_category_items_sprite(i, j, sprt);
        sfSprite_setPosition(sprt, PX_TO_MAPF((V2F(
            65.0f + (j % 2) * 120.0f, 139.0f + (i + 1) * 52.0f + (j / 2) *
            110.0f + (*offsetY)))));
        sfRenderWindow_drawSprite(Win.self, sprt, NULL);
    }
    (*offsetY) += 110.0f * ((cat->sheetCount + 1) / 2) + 10.0f;
}

///////////////////////////////////////////////////////////////////////////////
void draw_editor_browser(void)
{
    sfSprite *sprt = sfSprite_create();
    float offsetY = Editor.scrollingOffset;

    draw_rect(V2F(EDITOR_PANEL_W, Win.height - 84.0f), V2F(0.0f, 84.0f),
        EDITOR_WIDGET);
    for (uint_t i = 0; i < Editor.zone->categoryCount; i++) {
        draw_editor_browser_category(i, offsetY);
        if (Editor.zone->categories[i]->expand)
            draw_editor_browser_category_items(i, &offsetY, sprt);
    }
    sfSprite_destroy(sprt);
}
