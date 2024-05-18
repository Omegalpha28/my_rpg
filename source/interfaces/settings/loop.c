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

static char *conv(char key)
{
    char *str = malloc(2);

    str[0] = key;
    str[1] = '\0';
    return str;
}

///////////////////////////////////////////////////////////////////////////////
static sfColor get_color(v2f_t pos)
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
    if (CLICK_REL)
        Engine.scene = Setting.last_scene;
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}

static void draw_button(void)
{
    float up = 3.0f * 16.0f * Win.width / Win.viewWidth * 0.45f;
    sfSprite *bac = sfSprite_create();
    v2f_t pos = {Win.width / 2.0f, Win.height - up * 4 / 3};
    string_t left = conv(Setting.left.code + 'a');
    string_t right = conv(Setting.right.code + 'a');

    sfSprite_setTexture(bac, Assets.ui[UI_KEY]->self, false);
    sfSprite_setOrigin(bac, V2F(5.5f, 6.0f));
    sfSprite_setPosition(bac, PX_TO_MAPF(V2F(up, up + up / 5)));
    sfRenderWindow_drawSprite(Win.self, bac, false);
    sfSprite_setPosition(bac, PX_TO_MAPF(V2F(Win.width - up, up + up / 5)));
    sfRenderWindow_drawSprite(Win.self, bac, false);
    sfSprite_destroy(bac);
    draw_text_center(left, V2F(up, up + up / 5 - up / 6), 0.3f,
        sfColor_fromRGB(124, 137, 138));
    draw_text_center(right, V2F(Win.width - up, up + up / 5 - up / 6), 0.3f,
        sfColor_fromRGB(124, 137, 138));
    free(left);
    free(right);
    draw_text_center("Back", pos, 0.45f, get_color(PX_TO_MAPF(pos)));
}

///////////////////////////////////////////////////////////////////////////////
static void draw_colums(void)
{
    float scal = 7.5f * 16.0f * Win.width / Win.viewWidth * 0.45f;
    float up = 3.0f * 16.0f * Win.width / Win.viewWidth * 0.45f;
    sfSprite *bac = sfSprite_create();

    Setting.hover = false;
    draw_shadow();
    sfSprite_setTexture(bac, Assets.ui[UI_BAR]->self, false);
    sfSprite_setOrigin(bac, V2F(230.0f, 13.0f));
    sfSprite_setPosition(bac, PX_TO_MAPF(V2F(Win.width / 2, up + up / 5)));
    sfSprite_setScale(bac, V2F(0.85f, 1.0f));
    sfRenderWindow_drawSprite(Win.self, bac, false);
    sfSprite_destroy(bac);
    draw_text_right("Audio", V2F(Win.width / 2.0f - scal, up),
        0.45f, colums(V2F(Win.width / 2.0f - scal, up), "Audio", 0.45f, 3));
    draw_text_center("Video", V2F(Win.width / 2.0f, up),
        0.45f, colums(V2F(Win.width / 2.0f, up), "Video", 0.45f, 2));
    draw_text("Keybinds", PX_TO_MAPF(V2F(Win.width / 2.0f + scal, up)),
        0.45f, colums(V2F(Win.width / 2.0f + scal, up),
        "Keybinds", 0.45f, 1));
    draw_button();
}

///////////////////////////////////////////////////////////////////////////////
void draw_shadow(void)
{
    v2f_t pos = {0.0f, 0.0f};
    sfRectangleShape *shadow = sfRectangleShape_create();

    sfRectangleShape_setPosition(shadow, PX_TO_MAPF(pos));
    sfRectangleShape_setSize(shadow, V2F(Win.width, Win.height));
    sfRectangleShape_setFillColor(shadow, RGBA(35, 21, 39, 200));
    sfRenderWindow_drawRectangleShape(Win.self, shadow, false);
    sfRectangleShape_destroy(shadow);
}

///////////////////////////////////////////////////////////////////////////////
void settings_loop(void)
{
    sfEvent evt;

    CLICK_REL = false;
    KEY_REL = false;
    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
        CLICK_REL = click_rel(evt);
        KEY_REL = key_rel(evt);
        if (evt.key.code == Setting.pause.code)
            Engine.scene = Setting.last_scene;
        Engine.colum += (evt.key.code == Setting.left.code &&
            Engine.colum != 3);
        Engine.colum -= (evt.key.code == Setting.right.code &&
            Engine.colum != 1);
    }
    draw_menu_background();
    draw_colums();
    draw_cursor();
}
