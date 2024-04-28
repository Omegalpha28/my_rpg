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
void draw_menu_background(void)
{
    sfSprite *back = sfSprite_create();

    sfSprite_setTexture(back, Assets.ui[UI_BACKGROUND]->self, false);
    sfSprite_setPosition(back, PX_TO_MAPF(((v2f_t){0.0f, 0.0f})));
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

static void button_functions(float y)
{
    sfBool pressed = sfMouse_isButtonPressed(sfMouseLeft);
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};

    if (pressed && y == pos.y + 125)
        Engine.scene = SCENE_GAME;
    if (pressed && y == pos.y + 150)
        Engine.scene = SCENE_SETTINGS;
    if (pressed && y == pos.y + 175) {
        Engine.scene = SCENE_LEVEL_EDITOR;
        load_zone("biome1");
        Editor.zone = Assets.zones[0];
    }
    if (pressed && y == pos.y + 200)
        sfRenderWindow_close(Win.self);
}

static sfColor get_color(float y)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};
    sfSprite *select;

    RETURN(mouse.x > pos.x + 250 || mouse.x < pos.x + 50, sfWhite);
    RETURN(!(mouse.y >= (y - 10) && mouse.y <= (y + 15)), sfWhite);
    select = sfSprite_create();
    sfSprite_setTexture(select, Assets.ui[UI_DUAL_MARK]->self, false);
    sfSprite_setPosition(select, V2F(32 + pos.x, y - 8));
    sfRenderWindow_drawSprite(Win.self, select, NULL);
    sfSprite_destroy(select);
    button_functions(y);
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
    draw_text("Play", V2F(pos.x + 110, pos.y + 125),
        0.45F, get_color(pos.y + 125));
    draw_text("Settings", V2F(pos.x + 97, pos.y + 150),
        0.45F, get_color(pos.y + 150));
    draw_text("Level editor", V2F(pos.x + 87, pos.y + 175),
        0.45F, get_color(pos.y + 175));
    draw_text("Quit", V2F(pos.x + 110, pos.y + 200),
        0.45F, get_color(pos.y + 200));
}
