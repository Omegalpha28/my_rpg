/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** objects
*/

#ifndef OBJECTS_H_
    #define OBJECTS_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "moon.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Actor class, used to display a creature
///
/// \param self         The creature reference
/// \param sheetId      The current sheet used
/// \param animId       The current animation of the actor
/// \param isVariant    Boolean, if the skin is a variant or original
/// \param variantId    The index of the variant
/// \param position     The position of the actor
/// \param size         The size of the actor
/// \param rotation     The rotation of the actor
/// \param draw         Boolean, the actor is needed to be drawn
/// \param time         The starting time of the animation
/// \param done         Is the animation completed
/// \param old_pos      The old position of the actor before he moved
/// \param health       The health of the actor
/// \param invicinble   Is the actor invincible
/// \param damaged      Is the actor damaged
/// \param dead         Is the actor dead
/// \param shield       Number of shield of the actor
/// \param charges      Number of charges of the actor capacity
///
///////////////////////////////////////////////////////////////////////////////
typedef struct actor_s {
    creature_t *self;
    sfSprite *sprite;
    uint_t sheetId;
    uint_t animId;
    uint_t frame;
    bool_t isVariant;
    uint_t variantId;
    v2f_t position;
    v2f_t scale;
    float rotation;
    bool_t draw;
    ulong_t time;
    bool_t done;
    v2f_t old_pos;
    int health;
    bool_t invincible;
    bool_t damaged;
    bool_t dead;
    uint_t shield;
    uint_t charges;
} actor_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief State of the weapon bullets
///
///////////////////////////////////////////////////////////////////////////////
typedef enum bullet_state_e {
    BULLET_STATE_FLYING,
    BULLET_STATE_IMPACT,
    BULLET_STATE_DESTROYED,
    BULLET_STATE_COUNT
} bullet_state_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Structure to hold a bullet
///
/// \param weapon       The weapon used to shoot the bullet
/// \param img          The current img of the bullet
/// \param startAt      The currentTime when shooting the bullet
/// \param sender       The sender actor
/// \param origin       The origin of the bullet
/// \param position     The current position of the bullet
/// \param destination  The destination of the bullet
/// \param sprite       The sprite of the bullets
/// \param state        The state of the bullet
/// \param rotation     The rotation applied based on position/destination
///
///////////////////////////////////////////////////////////////////////////////
typedef struct bullet_s {
    uint_t weapon;
    image_t *img;
    ulong_t startAt;
    actor_t *sender;
    v2f_t origin;
    v2f_t position;
    v2f_t destination;
    sfSprite *sprite;
    bullet_state_t state;
    float rotation;
} bullet_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Prop class, used to draw map
///
/// \param self         References to the sheet of the prop
/// \param sprite       The sprite used to draw
/// \param frame        The current frame of the animation
/// \param animated     Boolean, is the prop animated or animation playing
/// \param position     The position of the prop in the world
/// \param scale        The scale of the prop in the world
/// \param rotation     The rotation of the prop
/// \param draw         True if the prop should be drawn, false otherwise
/// \param time         Starting time of the animation
/// \param once         Is the animation a one shot animation
/// \param done         Is the animation completed
/// \param collision    Is the prop has collision
/// \param data         Custom data saved in the prop to have various info
///
///////////////////////////////////////////////////////////////////////////////
typedef struct prop_s {
    sheet_t *self;
    sfSprite *sprite;
    uint_t frame;
    bool_t animated;
    v2f_t position;
    v2f_t scale;
    float rotation;
    bool_t draw;
    ulong_t time;
    ulong_t once;
    bool_t done;
    bool_t collision;
    byte_t data[4];
} prop_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Structure to hold an effect
///
/// \param self         The vfx that the vfx linked to
/// \param position     The position of the effect
/// \param frame        The current frame of the effect
/// \param isDecal      If the effect is a decal
/// \param fixFrame     Fix the frame to be the last one
///
///////////////////////////////////////////////////////////////////////////////
typedef struct effect_s {
    vfx_t *self;
    sfSprite *sprite;
    v2f_t position;
    uint_t frame;
    ulong_t time;
    bool_t isDecal;
    bool_t fixFrame;
} effect_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Type of interactable
///
///////////////////////////////////////////////////////////////////////////////
typedef enum interactable_type_e {
    INTERACTABLE_WEAPON,
    INTERACTABLE_CURRENCY,
    INTERACTABLE_PNJ,
    INTERACTABLE_CHEST,
    INTERACTABLE_COUNT
} interactable_type_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Structure to hold every interactables of the level
///
/// \param type         The type of interactable
/// \param data         The data of the interactable
/// \param time         The time of appearance of the interactable
/// \param position     The position of the interactable
/// \param interact     The function used on interaction with this object
/// \param sprite       The sprite of the object
/// \param img          The image of the object
///
///////////////////////////////////////////////////////////////////////////////
typedef struct interactable_s {
    interactable_type_t type;
    int data[4];
    ulong_t time;
    v2f_t position;
    void (*interact)(struct interactable_s *obj);
    sfSprite *sprite;
    image_t *img;
} interactable_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Object pool to keep track of loaded and drawed assets
///
/// \param actors       The list of actors
/// \param actorCount   The number of actors
/// \param props        The list of props
/// \param propCount    The number of props
/// \param effects      The list of effects
/// \param effectCount  The number of effects
/// \param bullets      The list of bullets
/// \param bulletCount  The number of bullet
/// \param sounds       The list of sounds
/// \param soundCount   The number of sound
/// \param inters       The list of interactables objects
/// \param interCount   The number of interactable object
///
///////////////////////////////////////////////////////////////////////////////
extern struct pool_s {
    actor_t **actors;
    uint_t actorCount;
    prop_t **props;
    uint_t propCount;
    effect_t **effects;
    uint_t effectCount;
    bullet_t **bullets;
    uint_t bulletCount;
    sfSound **sounds;
    uint_t soundCount;
    interactable_t **inters;
    uint_t interCount;
} Pool;

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new actor base on a creature and a position
///
/// \param creature     The reference creature for the actor
/// \param position     The default position of the actor
///
/// \return The newly created actor
///
///////////////////////////////////////////////////////////////////////////////
actor_t *actor_create(creature_t *creature, v2f_t position);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy the actor and remove it from the pool
///
/// \param act          The actor to destroy
///
///////////////////////////////////////////////////////////////////////////////
void actor_destroy(actor_t *act);

///////////////////////////////////////////////////////////////////////////////
/// \brief Move the actor base of an offset
///
/// \param act          The actor to move
/// \param offset       Vector2f of the deplacement offset
///
///////////////////////////////////////////////////////////////////////////////
void actor_move(actor_t *act, v2f_t offset);

///////////////////////////////////////////////////////////////////////////////
/// \brief Rotate the actor base of an angle
///
/// \param act          The actor to rotate
/// \param angle        Float angle to add to the actor
///
///////////////////////////////////////////////////////////////////////////////
void actor_rotate(actor_t *act, float angle);

///////////////////////////////////////////////////////////////////////////////
/// \brief Scale an actor base of factors
///
/// \param act          The actor to scale
/// \param factors      Scaling factors applied to the actor
///
///////////////////////////////////////////////////////////////////////////////
void actor_scale(actor_t *act, v2f_t factors);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw the actor on the screen if need to be drawed, and with the
/// current animation
///
/// \param act          The actor to draw
///
///////////////////////////////////////////////////////////////////////////////
void actor_draw(actor_t *act);

///////////////////////////////////////////////////////////////////////////////
/// \brief Set the actor active sheet using the index of the sheet
///
/// \param act          The focused actor
/// \param id           The index of the wanted sheet
///
/// \return True if the sheet has been updated, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_sheet_id(actor_t *act, uint_t id);

///////////////////////////////////////////////////////////////////////////////
/// \brief Set the actor active sheet using the name of the sheet
///
/// \param act          The focused actor
/// \param name         The name of the wanted sheet
///
/// \return True if the sheet has been updated, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_sheet(actor_t *act, cstring_t name);

///////////////////////////////////////////////////////////////////////////////
/// \brief Set the actor active animation using the index of the animation
///
/// \param act          The focused actor
/// \param id           The index of the wanted animation
///
/// \return True if the animation has been updated, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_anim_id(actor_t *act, uint_t id);

///////////////////////////////////////////////////////////////////////////////
/// \brief Set the actor active animation using the name of the animation
///
/// \param act          The focused actor
/// \param name         The name of the wanted animation
///
/// \return True if the animation has been updated, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_anim(actor_t *act, cstring_t name);

///////////////////////////////////////////////////////////////////////////////
/// \brief Set the actor active varaint using the name or the index of the
/// variant
///
/// \param act          The focused actor
/// \param name         The name of the wanted variant
/// \param id           The index of the wanted variant
///
/// \return True if the variant has been updated, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t actor_set_variant(actor_t *act, cstring_t name, uint_t id);

///////////////////////////////////////////////////////////////////////////////
/// \brief Refresh the transformation of the prop, applying the new transform
/// to the sprite
///
/// \param prop         The prop for updating
///
///////////////////////////////////////////////////////////////////////////////
void prop_set_transform(prop_t *prop);

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a prop base on a sprite sheet
///
/// \param sheet        The reference sheet
/// \param position     The position of the prop
/// \param rotation     The rotation of the prop
/// \param scale        The scale of the prop
///
///////////////////////////////////////////////////////////////////////////////
prop_t *prop_create(sheet_t *sheet, v2f_t position, v2f_t scale,
    float rotation);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy a prop, removing it from the pool
///
///////////////////////////////////////////////////////////////////////////////
void prop_destroy(prop_t *prop);

///////////////////////////////////////////////////////////////////////////////
/// \brief Move a prop by a certain offset
///
/// \param prop         The prop to move
/// \param offset       The offset to apply to the prop
///
///////////////////////////////////////////////////////////////////////////////
void prop_move(prop_t *prop, v2f_t offset);

///////////////////////////////////////////////////////////////////////////////
/// \brief Rotate a prop by a certain angle
///
/// \param prop         The prop to rotate
/// \param angle        The angle to apply to the prop
///
///////////////////////////////////////////////////////////////////////////////
void prop_rotate(prop_t *prop, float angle);

///////////////////////////////////////////////////////////////////////////////
/// \brief Scale a prop by factors
///
/// \param prop         The prop to scale
/// \param factors      The factors applied to the prop
///
///////////////////////////////////////////////////////////////////////////////
void prop_scale(prop_t *prop, v2f_t factors);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw a prop
///
/// \param draw         The prop to draw
///
///////////////////////////////////////////////////////////////////////////////
void prop_draw(prop_t *prop);

///////////////////////////////////////////////////////////////////////////////
/// \brief Load all the assets of a category
///
/// \param cat          The category to load
///
///////////////////////////////////////////////////////////////////////////////
void load_category(category_t *cat);

///////////////////////////////////////////////////////////////////////////////
/// \brief Unload all the assets of a category
///
/// \param cat          The category to unload
///
///////////////////////////////////////////////////////////////////////////////
void unload_category(category_t *cat);

///////////////////////////////////////////////////////////////////////////////
/// \brief Load a specific zone using the name
///
/// \param name         The name of the zone to load
///
/// \return Boolean of the status of loading, True if loaded, false if not
/// found
///
///////////////////////////////////////////////////////////////////////////////
bool_t load_zone(cstring_t name);

///////////////////////////////////////////////////////////////////////////////
/// \brief Unload a specific zone using the name
///
/// \param name         The name of the zone to unload
///
/// \return Boolean of the status of unloading, True if loaded, false if not
/// found
///
///////////////////////////////////////////////////////////////////////////////
bool_t unload_zone(cstring_t name);

///////////////////////////////////////////////////////////////////////////////
/// \brief Unload a specific image
///
/// \param img          The image to unload
///
///////////////////////////////////////////////////////////////////////////////
void unload_image(image_t *img);

///////////////////////////////////////////////////////////////////////////////
/// \brief Load a specific image
///
/// \param img          The image to load
///
///////////////////////////////////////////////////////////////////////////////
image_t *load_image(image_t *img);

///////////////////////////////////////////////////////////////////////////////
/// \brief Activate the animation of a prop
///
/// \param prop         The prop to animate
///
///////////////////////////////////////////////////////////////////////////////
void prop_animate(prop_t *prop);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy an effect and remove it from the Pool
///
/// \param eff          The effect to destroy
///
///////////////////////////////////////////////////////////////////////////////
void effect_destroy(effect_t *eff);

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new effect and append it to the Pool
///
/// \param source       The vfx sheet to be drawed
/// \param position     The position of the effect
/// \param isDecal      If the effect is a decal
///
/// \return The newly created effect or NULL if a failed occured
///
///////////////////////////////////////////////////////////////////////////////
effect_t *effect_create(vfx_t *source, v2f_t position, bool_t isDecal);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw an effect on the screen
///
/// \param eff          The effect to draw
///
///////////////////////////////////////////////////////////////////////////////
void effect_draw(effect_t *eff);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw an effect automatically on the screen
///
/// \param eff          The effect to draw
///
///////////////////////////////////////////////////////////////////////////////
void effect_draw(effect_t *eff);

///////////////////////////////////////////////////////////////////////////////
/// \brief Spawn an effect using his name
///
/// \param name         The name of the effect
/// \param position     The position of the effect
/// \param isDecal      If the effect is a decal
///
/// \return The effect structure or NULL if not found
///
///////////////////////////////////////////////////////////////////////////////
effect_t *effect(cstring_t name, v2f_t position, bool_t isDecal);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw all visible props (in view) of a list
///
/// \param list         The list of prop
/// \param n            The number of prop
///
///////////////////////////////////////////////////////////////////////////////
void draw_visible_props(prop_t **list, uint_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Play a sfx from the list
///
/// \param n            The sfx index from sfx_list
///
/// \return The newly created sound
///
///////////////////////////////////////////////////////////////////////////////
sfSound *sfx(sfx_list_t n);

///////////////////////////////////////////////////////////////////////////////
/// \brief Remove all not currently playing sound
///
///////////////////////////////////////////////////////////////////////////////
void remove_completed_sound(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Remove one sound from the pool
///
/// \param sd           The sound to remove
///
///////////////////////////////////////////////////////////////////////////////
void remove_sfx(sfSound *sd);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check player health.
///
///////////////////////////////////////////////////////////////////////////////
void check_player_health(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new interactable object and place it on the map
///
/// \param type         The type of interaction
/// \param position     The position of the object
/// \param firstData    The first data entry of the object
/// \param interact     The function to execute on interaction
///
/// \return The newly created interactable
///
///////////////////////////////////////////////////////////////////////////////
interactable_t *spawn_interactable(interactable_type_t type, v2f_t position,
    int firstData, void (*interact)(interactable_t *obj));

///////////////////////////////////////////////////////////////////////////////
/// \brief Remove and destroy an interactable from the pool
///
/// \param obj          The interactable object to destroy
///
///////////////////////////////////////////////////////////////////////////////
void destroy_interactable(interactable_t *obj);

#endif /* !OBJECTS_H_ */
