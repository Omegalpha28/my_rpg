/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** assets
*/

#ifndef ASSETS_H_
    #define ASSETS_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "moon.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Image structure, contain data about an image
///
/// \param filepath     The filepath of the image
/// \param self         The texture itself, NULL if not loaded
/// \param size         The size of the image in pixels
/// \param mask         The grid mask for animations
///
///////////////////////////////////////////////////////////////////////////////
typedef struct image_s {
    cstring_t filepath;
    sfTexture *self;
    v2u_t size;
    recti_t mask;
} image_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Animation structure, containing information about differents
/// variants
///
/// \param image        The image per default of the animation
/// \param variants     All the other images that can be used for this
///                     animation
/// \param variantCount The number of existing variants
/// \param name         The name of the animation, used to call the anim
/// \param frameCount   The number of frame of the animation
/// \param startingFrame The index of the starting frame
/// \param endingFrame  The index of the ending frame
/// \param looped       If the animation loop, otherwise get back to default
///
///////////////////////////////////////////////////////////////////////////////
typedef struct animation_s {
    image_t *image;
    image_t **variants;
    uint_t variantCount;
    cstring_t name;
    uint_t frameCount;
    uint_t startingFrame;
    uint_t endingFrame;
    bool_t looped;
} animation_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Creatures assets management structure
///
/// \param id           The creature's id, to determine the type of creature.
///                     By default 0 is for the player character
/// \param anims        Array of animations
/// \param animCount    Number of animation for the creature
/// \param miscs        Other image used for the creature
/// \param miscCount    The number of other image
///
///////////////////////////////////////////////////////////////////////////////
typedef struct assets_creatures_s {
    uint_t id;
    animation_t **anims;
    uint_t animCount;
    image_t **miscs;
    uint_t miscCount;
} assets_creatures_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Main assets structure for management
///
/// \param images       All the images of the game
/// \param imageCount   The number of image loaded to the game
/// \param creatures    The creatures array, used to store all the creatures
///                     and npc
/// \param creatureCount The number of creature in the array
///
///////////////////////////////////////////////////////////////////////////////
extern struct assets_s {
    image_t **images;
    uint_t imageCount;
    assets_creatures_t **creatures;
    uint_t creatureCount;
} Assets;

#endif /* !ASSETS_H_ */
