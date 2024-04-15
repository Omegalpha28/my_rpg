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
} actor_t;

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
} prop_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Object pool to keep track of loaded and drawed assets
///
/// \param actors       The list of actors
/// \param actorCount   The number of actors
/// \param props        The list of props
/// \param propCount    The number of props
///
///////////////////////////////////////////////////////////////////////////////
extern struct pool_s {
    actor_t **actors;
    uint_t actorCount;
    prop_t **props;
    uint_t propCount;
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
void load_image(image_t *img);

///////////////////////////////////////////////////////////////////////////////
void prop_animate(prop_t *prop);

#endif /* !OBJECTS_H_ */
