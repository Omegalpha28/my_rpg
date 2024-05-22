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

bool_t key_rel(sfEvent evt)
{
    return (evt.type == sfEvtKeyReleased);
}

bool_t click_rel(sfEvent evt)
{
    return (evt.type == sfEvtMouseButtonReleased &&
        evt.mouseButton.button == Setting.shoot);
}

static void display_info(axolotles_t *disp, uint_t id)
{
    char buff[11];
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;

    for (uint_t i = 0; i < AXO_COUNT; i++)
        Assets.axolotl[i]->disp = false;
    disp->disp = true;
    draw_text_center(disp->name, V2F(Win.width / 4 * 3,
        Win.height / 2 - move * 15), 0.45f, sfWhite);
    snprintf(buff, 10, "Health %d", disp->maxHealth);
    draw_text_center(buff, V2F(Win.width / 4 * 3 - move * 14,
        Win.height / 2 - move * 8), 0.35f, sfWhite);
    snprintf(buff, 9, "Speed %d", disp->speed);
    draw_text_center(buff, V2F(Win.width / 4 * 3 + move * 14,
        Win.height / 2 - move * 8), 0.35f, sfWhite);
    snprintf(buff, 11, "Shields %d", disp->shields);
    draw_text_center(buff, V2F(Win.width / 4 * 3,
        Win.height / 2 - move * 8), 0.35f, sfWhite);
    if (Engine.level == 1 && disp->grown == AXO_ADULT)
        change_player(disp->name, id);
}

static void change_sprite(axolotles_t *axo, sfSprite *slot)
{
    sfSprite_setTextureRect(slot, (sfIntRect){0, 0, 13, 17});
    sfSprite_setOrigin(slot, V2F(6.5f, 3.5f));
    if (axo->grown == AXO_EGG)
        sfSprite_setTexture(slot, axo->axolotl_egg->self, false);
    if (axo->grown > AXO_EGG) {
        sfSprite_setTextureRect(slot, (sfIntRect){0, 0, 24, 24});
        sfSprite_setOrigin(slot, V2F(12.0f, 12.0f));
    }
    if (axo->grown == AXO_BABY)
        sfSprite_setTexture(slot, axo->axolotl_baby->self, false);
    if (axo->grown == AXO_TEEN)
        sfSprite_setTexture(slot, axo->axolotl_teen->self, false);
    if (axo->grown == AXO_ADULT)
        sfSprite_setTexture(slot, axo->axolotl->self, false);
    sfRenderWindow_drawSprite(Win.self, slot, false);
}

static void draw_discovered(uint_t index, axolotles_t *axo)
{
    sfSprite *slot = sfSprite_create();
    float change = 16.0f * Win.width / Win.viewWidth * 1.5f;
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.x > PX_TO_MAPF(V2F1(change * 1.25f + change *
        (index % 9))).x && mouse.x < PX_TO_MAPF(V2F1(change * 2.25f + change *
        (index % 9))).x && mouse.y > PX_TO_MAPF(V2F1(Win.height / 2 - move *
        24 + move * (index - index % 9))).y && mouse.y < PX_TO_MAPF(
        V2F1(Win.height / 2 - move * 18 + move * (index - index % 9))).y;

    sfSprite_setPosition(slot, PX_TO_MAPF(V2F(change * 1.5 + change *
        (index % 9) + change / 2.75f, Win.height / 2 - move * 24 + move *
        (index - index % 9) + move / 2 + (mouse_in ? -move / 2 : 0))));
    if (mouse_in)
        Setting.hover = true;
    change_sprite(axo, slot);
    if ((mouse_in && CLICK_REL) || axo->disp)
        display_info(axo, index);
    sfSprite_destroy(slot);
}

static void draw_slots(void)
{
    sfSprite *slot = sfSprite_create();
    float change = 16.0f * Win.width / Win.viewWidth * 1.5f;
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;

    for (int i = 0; i < AXO_COUNT; i++) {
        sfSprite_setTexture(slot, Assets.ui[UI_LOCKED_AXO]->self, false);
        sfSprite_setPosition(slot, PX_TO_MAPF(V2F(change * 1.5 + change *
            (i % 9), Win.height / 2 - move * 24 + move * (i - i % 9))));
        if (Assets.axolotl[i]->grown)
            sfSprite_setTexture(slot, Assets.ui[UI_UNLOCK_AXO]->self, false);
        if (Assets.axolotl[i]->disp)
            sfSprite_setTexture(slot, Assets.ui[UI_SELECT_AXO]->self, false);
        sfRenderWindow_drawSprite(Win.self, slot, false);
        if (Assets.axolotl[i]->grown)
            draw_discovered(i, Assets.axolotl[i]);
    }
    sfSprite_destroy(slot);
}

void draw_squares_relay(void)
{
    sfRectangleShape *rec = sfRectangleShape_create();
    float change = 24.0f * Win.width / Win.viewWidth;
    float move = 3.60f * Win.height / Win.viewHeight;
    v2f_t pos = {change * 1.5 - change * 4 / 9, Win.height / 2 - move * 27};

    sfRectangleShape_setPosition(rec, PX_TO_MAPF(pos));
    sfRectangleShape_setSize(rec, V2F(24.0f * 3840 / Win.viewWidth * 11 / 9,
        3.60f * 2400 / Win.viewHeight * 7));
    sfRectangleShape_setFillColor(rec, RGB(68, 57, 84));
    sfRenderWindow_drawRectangleShape(Win.self, rec, false);
    sfRectangleShape_destroy(rec);
}

void draw_squares(void)
{
    sfSprite *box = sfSprite_create();
    sfSprite *name = sfSprite_create();
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;
    v2f_t posing = {Win.width / 4 * 3, Win.height / 2 - move * 19};

    sfSprite_setTexture(box, Assets.ui[UI_BOX_STAT]->self, false);
    sfSprite_setOrigin(box, V2F(52.5f, 0.0f));
    sfSprite_setPosition(box, PX_TO_MAPF(posing));
    sfSprite_setScale(box, V2F(1.75f, 1.5f));
    sfSprite_setTexture(name, Assets.ui[UI_BASE_NAME]->self, false);
    sfSprite_setOrigin(name, V2F(91.0f, -28.0f));
    sfSprite_setPosition(name, PX_TO_MAPF(posing));
    sfSprite_setScale(name, V2F(0.50f, 0.30f));
    sfRenderWindow_drawSprite(Win.self, box, false);
    sfRenderWindow_drawSprite(Win.self, name, false);
    sfSprite_destroy(box);
    sfSprite_destroy(name);
    draw_squares_relay();
}

static void draw_bacs(void)
{
    v2f_t pos = {0.0f, 0.0f};
    sfRectangleShape *shadow = sfRectangleShape_create();
    sfSprite *pattern = sfSprite_create();

    sfRectangleShape_setPosition(shadow, PX_TO_MAPF(pos));
    sfRectangleShape_setSize(shadow, V2F(Win.width, Win.height));
    sfRectangleShape_setFillColor(shadow, RGB(121, 167, 202));
    sfRenderWindow_drawRectangleShape(Win.self, shadow, false);
    sfSprite_setTexture(pattern, Assets.ui[UI_PATTERN_AXO]->self, false);
    sfSprite_setColor(pattern, RGB(113, 152, 201));
    for (uint_t i = 0; i < 30; i++) {
        sfSprite_setPosition(pattern, PX_TO_MAPF(V2F(i % 4 * 130 * Win.width /
            Win.viewWidth, (i - i % 4) * 12 * Win.height / Win.viewHeight)));
        sfRenderWindow_drawSprite(Win.self, pattern, false);
    }
    sfRectangleShape_destroy(shadow);
    draw_squares();
}

void inventory_loop(void)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
        CLICK_REL = click_rel(evt);
        if (evt.type == sfEvtKeyReleased &&
            (evt.key.code == Setting.inventory.code ||
            evt.key.code == Setting.pause.code))
            Engine.scene = SCENE_GAME;
    }
    Setting.hover = false;
    draw_bacs();
    draw_slots();
    draw_cursor();
}
