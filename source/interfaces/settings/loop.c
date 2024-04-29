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

static void draw_colums(void)
{
    return;
}

///////////////////////////////////////////////////////////////////////////////
static void draw_shadow(void)
{
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};
    sfRectangleShape *shadow = sfRectangleShape_create();

    sfRectangleShape_setPosition(shadow, pos);
    sfRectangleShape_setSize(shadow, V2F(Win.width, Win.height));
    sfRectangleShape_setFillColor(shadow, RGBA(0, 0, 0, 50));
    sfRenderWindow_drawRectangleShape(Win.self, shadow, false);
    sfRectangleShape_destroy(shadow);
}

///////////////////////////////////////////////////////////////////////////////
static void button_functions(float y)
{
    sfBool pressed = sfMouse_isButtonPressed(sfMouseLeft);
    v2f_t pos = {-32.0f * 0.45f, Win.viewHeight / 2.0f - 30.0f};

    if (pressed && y == pos.y)
        Engine.scene = SCENE_MAIN_MENU;
}

///////////////////////////////////////////////////////////////////////////////
static sfColor get_color(v2f_t pos)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfSprite *select;

    RETURN(mouse.x > 50 || mouse.x < -25, sfWhite);
    RETURN(!(mouse.y >= (pos.y - 10) && mouse.y <= (pos.y + 15)), sfWhite);
    Keys.hover = true;
    select = sfSprite_create();
    sfSprite_setTexture(select, Assets.ui[UI_DUAL_MARK_SMALL]->self, false);
    sfSprite_setPosition(select, V2F(pos.x - 55, pos.y - 8));
    sfRenderWindow_drawSprite(Win.self, select, NULL);
    sfSprite_destroy(select);
    button_functions(pos.y);
    return (sfColor_fromRGB(243, 199, 77));
}

///////////////////////////////////////////////////////////////////////////////
void settings_loop(void)
{
    sfEvent evt;
    v2f_t pos = {-32.0f * 0.45f, Win.viewHeight / 2.0f - 30.0f};

    while (sfRenderWindow_pollEvent(Win.self, &evt))
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
    draw_menu_background();
    draw_shadow();
    draw_colums();
    Keys.hover = false;
    draw_text("Back", pos, 0.45f, get_color(pos));
    draw_cursor();
}
