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

static void display_info(axolotles_t *disp)
{
    char maxhealth[10];
    char shield[11];
    char speed[9];
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;

    for (uint_t i = 0; i < AXO_COUNT; i++)
        Assets.axolotl[i]->disp = false;
    disp->disp = true;
    snprintf(shield, 11, "Shields %d", disp->shields);
    snprintf(speed, 9, "Speed %d", disp->speed);
    snprintf(maxhealth, 10, "Health %d", disp->maxHealth);
    draw_text_center(disp->name, V2F(Win.width / 4 * 3,
        Win.height / 2 - move * 15), 0.45f, sfWhite);
    draw_text_center(maxhealth, V2F(Win.width / 4 * 3 - move * 18,
        Win.height / 2 - move * 11), 0.35f, sfWhite);
    draw_text_center(speed, V2F(Win.width / 4 * 3 + move * 18,
        Win.height / 2 - move * 11), 0.35f, sfWhite);
    draw_text_center(shield, V2F(Win.width / 4 * 3,
        Win.height / 2 - move * 11), 0.35f, sfWhite);
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

static void draw_discovered(uint_t index, sfSprite *slot, axolotles_t *axo)
{
    float change = 16.0f * Win.width / Win.viewWidth * 1.5f;
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t mouse_in = mouse.x > PX_TO_MAPF(V2F1(change * 1.25f + change *
        (index % 9))).x && mouse.x < PX_TO_MAPF(V2F1(change * 2.25f + change *
        (index % 9))).x && mouse.y > PX_TO_MAPF(V2F1(Win.height / 2 - move *
        24 + move * (index - index % 9))).y && mouse.y < PX_TO_MAPF(
        V2F1(Win.height / 2 - move * 18 + move * (index - index % 9))).y;

    change_sprite(axo, slot);
    if (mouse_in)
        Setting.hover = true;
    if ((mouse_in && CLICK_REL) || axo->disp)
        display_info(axo);
}

static void draw_slots(void)
{
    sfSprite *slot = sfSprite_create();
    sfSprite *axo = sfSprite_create();
    float change = 16.0f * Win.width / Win.viewWidth * 1.5f;
    float move = 16.0f * Win.height / Win.viewHeight / 10 * 1.5f * 1.5f;

    sfSprite_setTexture(slot, Assets.ui[UI_LOCKED_AXO]->self, false);
    for (int i = 0; i < AXO_COUNT; i++) {
        sfSprite_setPosition(slot, PX_TO_MAPF(V2F(change * 1.5 + change *
            (i % 9), Win.height / 2 - move * 24 + move * (i - i % 9))));
        sfRenderWindow_drawSprite(Win.self, slot, false);
        sfSprite_setPosition(axo, PX_TO_MAPF(V2F(change * 1.5 + change *
            (i % 9) + change / 2.75f, Win.height / 2 - move * 24 + move *
            (i - i % 9) + move / 2)));
        if (Assets.axolotl[i]->grown)
            draw_discovered(i, axo, Assets.axolotl[i]);
    }
    sfSprite_destroy(axo);
    sfSprite_destroy(slot);
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
    draw();
    draw_shadow();
    draw_slots();
    draw_cursor();
}
