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

static void button_functions(float y)
{
    sfBool pressed = sfMouse_isButtonPressed(sfMouseLeft);
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};

    if (pressed && y == -pos.y - 50)
        Engine.scene = SCENE_MAIN_MENU;
}

static sfColor get_color(float x, float y)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfSprite *select;

    RETURN(mouse.x > 50 || mouse.x < -25, sfWhite);
    RETURN(!(mouse.y >= (y - 10) && mouse.y <= (y + 15)), sfWhite);
    select = sfSprite_create();
    sfSprite_setTexture(select, Assets.ui[UI_DUAL_MARK_SMALL]->self, false);
    sfSprite_setPosition(select, V2F(x - 56, y - 8));
    sfRenderWindow_drawSprite(Win.self, select, NULL);
    sfSprite_destroy(select);
    button_functions(y);
    return (sfColor_fromRGB(243, 199, 77));
}

void settings_loop(void)
{
    sfEvent evt;
    v2f_t pos = {-Win.viewWidth / 2, -Win.viewHeight / 2};

    while (sfRenderWindow_pollEvent(Win.self, &evt))
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
    draw_menu_background();
    draw_shadow();
    draw_text("Back", V2F(-25, -pos.y - 50),
        0.45F, get_color(-25, -pos.y - 50));
}
