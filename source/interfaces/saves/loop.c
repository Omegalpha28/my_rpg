/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void draw_profile_background(v2f_t position, ui_element_t item)
{
    sfSprite *back = sfSprite_create();

    sfSprite_setScale(back, V2F(1.0f, 0.65f));
    sfSprite_setTexture(back, Assets.ui[item]->self, false);
    sfSprite_setTextureRect(back, (recti_t){0, 0, 10, 56});
    sfSprite_setPosition(back, position);
    sfRenderWindow_drawSprite(Win.self, back, NULL);
    sfSprite_setTextureRect(back, (recti_t){15, 0, 10, 56});
    for (uint_t i = 0; i < 12; i++) {
        sfSprite_setPosition(back, add2f(position, V2F(10.0f + i * 10.0f,
            0.0f)));
        sfRenderWindow_drawSprite(Win.self, back, NULL);
    }
    sfSprite_setTextureRect(back, (recti_t){39, 0, 10, 56});
    sfSprite_setPosition(back, add2f(position, V2F(10.0f * 13, 0.0f)));
    sfRenderWindow_drawSprite(Win.self, back, NULL);
    sfSprite_destroy(back);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_profile_delete(v2f_t position, v2f_t ratio, uint_t id)
{
    sfSprite *del = sfSprite_create();
    recti_t mask = Assets.ui[UI_BUTTON_BIN_IDLE]->mask;
    bool_t hover = cursor_inbound(MAP_TO_PXF(subtract2f(position, V2F(
        mask.width * 0.6f / 2.0f, mask.height * 0.6f /
        2.0f))), V2F(mask.width * ratio.x * 0.6f, mask.height * ratio.y *
        0.6f));

    Setting.hover = hover ? true : Setting.hover;
    sfSprite_setTexture(del, hover ? Assets.ui[UI_BUTTON_BIN_PRESSED]->self :
        Assets.ui[UI_BUTTON_BIN_IDLE]->self, false);
    sfSprite_setOrigin(del, V2F(mask.width / 2.0f, mask.height / 2.0f));
    sfSprite_setScale(del, V2F1(0.6f));
    sfSprite_setPosition(del, position);
    if (hover && MPRESSED(Setting.shoot))
        delete_save(id);
    sfRenderWindow_drawSprite(Win.self, del, NULL);
    sfSprite_destroy(del);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_profile_click(uint_t id)
{
    Engine.saveId = id;
    if (!exist_save(id)) {
        load_video(DIR_INTRO, "intro");
        Engine.level = 1;
    } else {
        Engine.scene = SCENE_GAME;
        load_save(id);
        Engine.level = 0;
        switch_level();
    }
}

///////////////////////////////////////////////////////////////////////////////
static void draw_profile_text(uint_t id, bool_t exists, v2f_t position)
{
    char text[32];

    if (exists)
        return (draw_text_center("New Save", MAP_TO_PXF(add2f(position,
            V2F(72.0f, 13.0f))), 0.5f, RGB(235, 235, 235)));
    load_save(id - 1);
    snprintf(text, 32, "%luhrs %lumin", Engine.spent / 60, Engine.spent % 60);
    draw_text_center(text, MAP_TO_PXF(add2f(position, V2F(72.0f, 13.0f))),
        0.5f, RGB(235, 235, 235));
}

///////////////////////////////////////////////////////////////////////////////
static void draw_save_profile(uint_t id)
{
    v2f_t position = {-200.0f, id * 41.4f - 20.0f};
    v2f_t ratio = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};
    bool_t hover = cursor_inbound(MAP_TO_PXF(position), V2F(140.0f * ratio.x,
        36.4f * ratio.y));
    bool_t exists = exist_save(id);

    Setting.hover = hover ? true : Setting.hover;
    draw_profile_background(!hover ? position : add2f(position,
        V2F(10.0f, 0.0f)), hover ? UI_PAPER_ITEM01 : UI_PAPER_ITEM02);
    if (exists)
        draw_profile_delete(add2f(position, V2F(180.0f, 36.4f / 2.0f)),
            ratio, id);
    position.x += hover ? 10.0f : 0.0f;
    draw_profile_text(exists, id, position);
    if (hover && MPRESSED(Setting.shoot))
        handle_profile_click(id);
}

///////////////////////////////////////////////////////////////////////////////
static void handle_saves_events(void)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
        if (evt.type == sfEvtKeyPressed && evt.key.code == sfKeyEscape)
            Engine.scene = SCENE_MAIN_MENU;
    }
}

///////////////////////////////////////////////////////////////////////////////
void saves_loop(void)
{
    Setting.hover = false;
    handle_saves_events();
    draw_menu_background();
    draw_levitating_logo();
    draw_save_profile(0);
    draw_save_profile(1);
    draw_save_profile(2);
    draw_cursor();
}
