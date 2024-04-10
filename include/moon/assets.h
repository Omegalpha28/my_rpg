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
//
// CONFIGURATION
//
///////////////////////////////////////////////////////////////////////////////

    /** Assets location                                                      */
    #define DIR_ASSETS "assets"
    #define DIR_CREATURES DIR_ASSETS "/creatures"
    #define DIR_EFFECTS DIR_ASSETS "/effects"
    #define DIR_UI DIR_ASSETS "/interfaces"
    #define DIR_MUSICS DIR_ASSETS "/musics"
    #define DIR_SOUNDS DIR_ASSETS "/sounds"
    #define DIR_WEAPONS DIR_ASSETS "/weapons"
    #define DIR_ZONES DIR_ASSETS "/zones"

    /** Assets configuration extensions                                      */
    #define EXT_CREATURE "creature"
    #define EXT_MUSICS "ogg"

    /** Default FrameRate                                                    */
    #define FRAME_PER_MS(x) (1000 / x)
    #define DEFAULT_CREATURE_FR FRAME_PER_MS(7)
    #define DEFAULT_PROP_FR 5

///////////////////////////////////////////////////////////////////////////////
/// \brief List of predefined creature index
///
///////////////////////////////////////////////////////////////////////////////
typedef enum creature_index_e {
    creaturePlayer,
    creatureDuck,
    CREATURE_COUNT
} creature_index_t;

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
    cstring_t name;
    cstring_t filepath;
    sfTexture *self;
    v2u_t size;
    v2u_t grid;
    recti_t mask;
} image_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Animation structure, containing information about differents
/// variants
///
/// \param name         The name of the animation, used to call the anim
/// \param frameCount   The number of frame of the animation
/// \param startingFrame The index of the starting frame
/// \param endingFrame  The index of the ending frame
/// \param looped       If the animation loop, otherwise get back to default
///
///////////////////////////////////////////////////////////////////////////////
typedef struct animation_s {
    cstring_t name;
    uint_t frameRate;
    uint_t frameCount;
    uint_t startingFrame;
    uint_t endingFrame;
    bool_t looped;
} animation_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Entry status, used to know if the instruction is in an entry
///
///////////////////////////////////////////////////////////////////////////////
typedef enum entry_status_e {
    entryNothing,
    entrySheet,
    entryMisc,
    ENTRY_COUNT
} entry_status_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Creature texture sheet management
///
/// \param name         The name of the sprite sheet
/// \param anims        Array of animations
/// \param animCount    Number of animation for the creature
/// \param image        The default image of the sheet
/// \param variants     All the other images that can be used for this
///                     animation
/// \param variantCount The number of existing variants/
///////////////////////////////////////////////////////////////////////////////
typedef struct sheet_s {
    cstring_t name;
    animation_t **anims;
    uint_t animCount;
    image_t *image;
    image_t **variants;
    uint_t variantCount;
} sheet_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Creatures assets management structure
///
/// \param id           The creature's id, to determine the type of creature.
///                     By default 0 is for the player character
/// \param sheets       The sheets array for each sprite sheet of the creature
/// \param sheetCount   The number of sprite sheets
/// \param miscs        Other image used for the creature
/// \param miscCount    The number of other image
///
///////////////////////////////////////////////////////////////////////////////
typedef struct creatures_s {
    uint_t id;
    sheet_t **sheets;
    uint_t sheetCount;
    image_t **miscs;
    uint_t miscCount;
    entry_status_t status;
} creatures_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Structure to hold the musics
///
/// \param name         The name of the music
/// \param self         The loaded instance of the music
///
///////////////////////////////////////////////////////////////////////////////
typedef struct music_s {
    cstring_t name;
    sfMusic *self;
} music_t;

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
    creatures_t **creatures;
    uint_t creatureCount;
    music_t **musics;
    uint_t musicCount;
} Assets;

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize every assets used in the game dynamically
///
/// \return True if everything is loaded, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new image base of a filepath and add's it to the pool
///
/// \param filepath     The path of the image
/// \param load         Boolean, do the image need to be load
/// \param grid         The grid used by the image
/// \param name         The name of the image, for variant
///
/// \return Returns the newly created image, or NULL if the image is not found
/// or if an error occured
///
///////////////////////////////////////////////////////////////////////////////
image_t *add_image(cstring_t filepath, bool_t load, v2u_t mask,
    cstring_t name);

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize the creature folder, each creature is alloced and loaded
/// automatically.
///
/// \return True if everything loaded correctly, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_creatures(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize all the musics of the game dynamically, preload it in the
/// memory to easily access it
///
/// \return True if everything loaded correctly, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_musics(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy the musics assets dynamically
///
///////////////////////////////////////////////////////////////////////////////
void destroy_assets_musics(void);

#endif /* !ASSETS_H_ */
