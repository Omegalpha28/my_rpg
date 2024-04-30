/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_cursor(void)
{
    sfSprite *cursor = sfSprite_create();
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfBool pressed = sfMouse_isButtonPressed(sfMouseLeft);
    sfIntRect rect = {0, 0, 20, 20};

    if (HOVER)
        rect.left += 20;
    if (pressed)
        rect.top = 20;
    if (DEAD)
        rect.left += 40;
    sfSprite_setPosition(cursor, mouse);
    sfSprite_setOrigin(cursor, V2F(7.0f, 7.0f));
    sfSprite_setTexture(cursor, Assets.ui[UI_CURSOR]->self, false);
    sfSprite_setTextureRect(cursor, rect);
    sfSprite_rotate(cursor, -35);
    sfSprite_setScale(cursor, (v2f_t){0.75f, 0.75f});
    sfRenderWindow_drawSprite(Win.self, cursor, false);
    sfSprite_destroy(cursor);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_autors(void)
{
    sfSprite *black = sfSprite_create();
    sfSprite *autors = sfSprite_create();

    sfSprite_setTexture(black, Assets.ui[UI_BLACK_FADE]->self, false);
    sfSprite_setTexture(autors, Assets.ui[UI_AUTORS_CORNER]->self, false);
    sfSprite_setPosition(black, PX_TO_MAPF((V2F1(0.0f))));
    sfSprite_setPosition(autors, PX_TO_MAPF((V2F(Win.width, Win.height))));
    sfSprite_setScale(black, V2F1(Win.viewWidth / 1701.0f));
    sfSprite_setScale(autors, V2F1(Win.viewWidth / 831.0f / 4));
    sfSprite_setOrigin(autors, V2F(831.0f, 381.0f));
    sfRenderWindow_drawSprite(Win.self, black, NULL);
    sfRenderWindow_drawSprite(Win.self, autors, NULL);
    sfSprite_destroy(black);
    sfSprite_destroy(autors);
}

///////////////////////////////////////////////////////////////////////////////
void draw_menu_background(void)
{
    sfSprite *back = sfSprite_create();

    sfSprite_setTexture(back, Assets.ui[UI_BACKGROUND]->self, false);
    sfSprite_setPosition(back, PX_TO_MAPF((V2F1(0.0f))));
    sfSprite_setScale(back, (v2f_t){Win.viewWidth / 1920.0f,
        Win.viewHeight / 1080.0f});
    sfRenderWindow_drawSprite(Win.self, back, NULL);
    sfSprite_destroy(back);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_logo(void)
{
    sfSprite *logo = sfSprite_create();
    float offsetY = 5.0f * sin((float)(Time.currentTime) / 1000.0f);
    v2f_t pos = {Win.viewWidth / 2, Win.viewHeight / 2};

    sfSprite_setTexture(logo, Assets.ui[UI_LOGO]->self, false);
    sfSprite_setScale(logo, V2F(0.15f, 0.15f));
    sfSprite_setColor(logo, sfColor_fromRGBA(0, 0, 0, 128));
    sfSprite_setPosition(logo, V2F(-pos.x, 30 + offsetY - pos.y));
    sfRenderWindow_drawSprite(Win.self, logo, NULL);
    sfSprite_setColor(logo, sfColor_fromRGB(255, 255, 255));
    sfSprite_setPosition(logo, V2F(-pos.x, 20 + offsetY - pos.y));
    sfRenderWindow_drawSprite(Win.self, logo, NULL);
    sfSprite_destroy(logo);
}

///////////////////////////////////////////////////////////////////////////////
static void button_functions(float y, sfEvent evt)
{
    bool_t pressed = (evt.type == sfEvtMouseButtonReleased);
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};

    if (pressed && y == pos.y + 125)
        Engine.scene = SCENE_GAME;
    if (pressed && y == pos.y + 150)
        Engine.scene = SCENE_SETTINGS;
    if (pressed && y == pos.y + 175) {
        sfRenderWindow_setMouseCursorVisible(Win.self, true);
        Engine.scene = SCENE_LEVEL_EDITOR;
        load_zone("biome1");
        Editor.zone = Assets.zones[0];
    }
    if (pressed && y == pos.y + 200)
        sfRenderWindow_close(Win.self);
}

///////////////////////////////////////////////////////////////////////////////
static sfColor get_color(float y, sfEvent evt)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};
    sfSprite *select;

    RETURN(mouse.x > pos.x + 200 || mouse.x < pos.x + 35, sfWhite);
    RETURN(!(mouse.y >= (y - 10) && mouse.y <= (y + 15)), sfWhite);
    Keys.hover = true;
    select = sfSprite_create();
    sfSprite_setTexture(select, Assets.ui[UI_DUAL_MARK]->self, false);
    sfSprite_setPosition(select, V2F(32 + pos.x, y - 8));
    sfRenderWindow_drawSprite(Win.self, select, NULL);
    sfSprite_destroy(select);
    button_functions(y, evt);
    return (sfColor_fromRGB(243, 199, 77));
}

///////////////////////////////////////////////////////////////////////////////
void menu_loop(void)
{
    sfEvent evt;
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};

    while (sfRenderWindow_pollEvent(Win.self, &evt))
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
    draw_menu_background();
    draw_logo();
    draw_autors();
    Keys.hover = false;
    draw_text("Play", V2F(pos.x + 110, pos.y + 125),
        0.45F, get_color(pos.y + 125, evt));
    draw_text("Settings", V2F(pos.x + 97, pos.y + 150),
        0.45F, get_color(pos.y + 150, evt));
    draw_text("Level editor", V2F(pos.x + 87, pos.y + 175),
        0.45F, get_color(pos.y + 175, evt));
    draw_text("Quit", V2F(pos.x + 110, pos.y + 200),
        0.45F, get_color(pos.y + 200, evt));
    draw_cursor();
}
