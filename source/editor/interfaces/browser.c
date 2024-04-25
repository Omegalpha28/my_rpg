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
    category_t *cat = Editor.zone->categories[i];
    v2f_t pos = V2F(15.0f, 84.0f + i * 52.0f + offsetY);
    v2f_t size = V2F(220.0f, EDITOR_PANEL_H);
    bool_t hover = cursor_inbound(pos, size);
    sfColor color = hover ? RGB(200, 0, 0) : sfRed;

    draw_rect(size, pos, color);
    if (hover && sfMouse_isButtonPressed(sfMouseLeft) && Editor.released) {
        cat->expand = !cat->expand;
        Editor.released = false;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void set_category_items_sprite(uint_t i, uint_t j, sfSprite *sprt,
    float offsetY)
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
    sfSprite_setPosition(sprt, PX_TO_MAPF((V2F(65.0f + (j % 2) * 120.0f,
        139.0f + (i + 1) * 52.0f + (j / 2) * 110.0f + offsetY))));
}

///////////////////////////////////////////////////////////////////////////////
static void handle_click_on_browser_item(sheet_t *sheet)
{
    prop_t ***arr = Editor.layer == EDITOR_LAYER_FOREGROUND ?
        &(Editor.fProps) : &(Editor.bProps);
    uint_t *counter = Editor.layer == EDITOR_LAYER_FOREGROUND ?
        &(Editor.fCount) : &(Editor.bCount);
    prop_t *prop = NULL;

    add_prop(sheet, arr, counter);
    prop = (*arr)[*(counter) - 1];
    prop->position = PX_TO_MAPF(V2F(Win.width / 2.0f, Win.height / 2.0f));
    prop->position.x = floorf(prop->position.x);
    prop->position.y = floorf(prop->position.y);
    prop_set_transform(prop);
    Editor.focus = prop;
    Editor.released = false;
}

///////////////////////////////////////////////////////////////////////////////
static void draw_editor_items_hover(v2f_t pos)
{
    bool_t pressed = sfMouse_isButtonPressed(sfMouseLeft);
    sfTexture *txt = pressed ? Assets.ui[UI_BUTTON_MORE_PRESSED]->self :
        Assets.ui[UI_BUTTON_MORE_IDLE]->self;
    sfSprite *sprt = sfSprite_create();
    v2u_t size = sfTexture_getSize(txt);

    sfSprite_setTexture(sprt, txt, false);
    sfSprite_setPosition(sprt, PX_TO_MAPF(add2f(pos, V2F1(50.0f))));
    sfSprite_setScale(sprt, multiply2f(FACTORS(size), V2F1(2.0f)));
    sfSprite_setOrigin(sprt, V2F(size.x / 2.0f, size.y / 2.0f));
    sfRenderWindow_drawSprite(Win.self, sprt, NULL);
    sfSprite_destroy(sprt);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_editor_browser_category_items(uint_t i, float *offsetY,
    sfSprite *sprt)
{
    category_t *cat = Editor.zone->categories[i];
    v2f_t pos = V2F1(0.0f);
    v2f_t size = V2F(100.0f, 100.0f);
    bool_t hover = false;

    for (uint_t j = 0; j < cat->sheetCount; j++) {
        pos.x = 15.0f + (j % 2) * 120.0f;
        pos.y = 89.0f + (i + 1) * 52.0f + (j / 2) * 110.0f + (*offsetY);
        hover = cursor_inbound(pos, size);
        draw_rect(size, pos, hover ? EDITOR_HOVER : EDITOR_BUTTON);
        if (hover && sfMouse_isButtonPressed(sfMouseLeft) && Editor.released)
            handle_click_on_browser_item(cat->sheets[j]);
        set_category_items_sprite(i, j, sprt, (*offsetY));
        sfRenderWindow_drawSprite(Win.self, sprt, NULL);
        if (hover)
            draw_editor_items_hover(pos);
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
