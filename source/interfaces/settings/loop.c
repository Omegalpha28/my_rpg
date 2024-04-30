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
static void draw_colums(void)
{
    float scal = 7.5f * 16.0f * Win.width / Win.viewWidth * 0.45f;
    float up = 3.0f * 16.0f * Win.width / Win.viewWidth * 0.45f;

    draw_text_right("Audio", V2F(Win.width / 2.0f - scal, up),
        0.45f, colums(V2F(Win.width / 2.0f - scal, up), "Audio", 0.45f, 3));
    draw_text_center("Video", V2F(Win.width / 2.0f, up),
        0.45f, colums(V2F(Win.width / 2.0f, up), "Video", 0.45f, 2));
    draw_text("Keybinds", PX_TO_MAPF(V2F(Win.width / 2.0f + scal, up)),
        0.45f, colums(V2F(Win.width / 2.0f + scal, up),
        "Keybinds", 0.45f, 1));
}

///////////////////////////////////////////////////////////////////////////////
static void draw_shadow(void)
{
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};
    sfRectangleShape *shadow = sfRectangleShape_create();

    sfRectangleShape_setPosition(shadow, pos);
    sfRectangleShape_setSize(shadow, V2F(Win.width, Win.height));
    sfRectangleShape_setFillColor(shadow, RGBA(35, 21, 39, 200));
    sfRenderWindow_drawRectangleShape(Win.self, shadow, false);
    sfRectangleShape_destroy(shadow);
}

///////////////////////////////////////////////////////////////////////////////
static void button_functions(sfEvent evt)
{
    sfBool pressed = (evt.type == sfEvtMouseButtonReleased &&
        evt.mouseButton.button == Setting.shoot);

    if (pressed)
        Engine.scene = SCENE_MAIN_MENU;
}

///////////////////////////////////////////////////////////////////////////////
static sfColor get_color(v2f_t pos, sfEvent evt)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfSprite *select;

    RETURN(mouse.x > 50 || mouse.x < -25, sfWhite);
    RETURN(!(mouse.y >= (pos.y - 10) && mouse.y <= (pos.y + 15)), sfWhite);
    Setting.hover = true;
    select = sfSprite_create();
    sfSprite_setTexture(select, Assets.ui[UI_DUAL_MARK_SMALL]->self, false);
    sfSprite_setPosition(select, V2F(pos.x - 69.5f, pos.y - 8));
    sfRenderWindow_drawSprite(Win.self, select, NULL);
    sfSprite_destroy(select);
    button_functions(evt);
    return (sfColor_fromRGB(243, 199, 77));
}

///////////////////////////////////////////////////////////////////////////////
void settings_loop(void)
{
    sfEvent evt;
    float scal = 4.0f * 16.0f * Win.width / Win.viewWidth * 0.45f;
    v2f_t pos = {Win.width / 2.0f, Win.height - scal};

    while (sfRenderWindow_pollEvent(Win.self, &evt))
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
    draw_menu_background();
    draw_shadow();
    draw_colums();
    Setting.hover = false;
    draw_text_center("Back", pos, 0.45f, get_color(PX_TO_MAPF(pos), evt));
    draw_cursor();
}
