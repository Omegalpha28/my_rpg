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
    #define DIR_VFX DIR_ASSETS "/vfx"
    #define DIR_UI DIR_ASSETS "/interfaces"
    #define DIR_MUSICS DIR_ASSETS "/musics"
    #define DIR_SOUNDS DIR_ASSETS "/sounds"
    #define DIR_WEAPONS DIR_ASSETS "/weapons"
    #define DIR_RELOADS DIR_WEAPONS "/reloads"
    #define DIR_ZONES DIR_ASSETS "/zones"
    #define DIR_VIDEO DIR_ASSETS "/videos"
    #define DIR_INTRO DIR_VIDEO "/intro"
    #define DIR_OUTRO DIR_VIDEO "/outro"

    /** Zones restricted name                                                */
    #define CAT_TRAP "traps"
    #define CAT_DOOR "doors"
    #define CAT_DESTRUCTIBLE "destructibles"

    /** Assets configuration extensions                                      */
    #define EXT_CREATURE "creature"
    #define EXT_MUSICS "ogg"

    /** Default FrameRate                                                    */
    #define FRAME_PER_MS(x) (1000 / x)
    #define DEFAULT_CREATURE_FR FRAME_PER_MS(8)
    #define DEFAULT_PROP_FR FRAME_PER_MS(5)
    #define DEFAULT_VFX_FR FRAME_PER_MS(6)
    #define VIDEO_FRAMERATE FRAME_PER_MS(12)

    /** Weapon Size                                                          */
    #define WEAPON_SHEET_W 256
    #define WEAPON_SHEET_H 160
    #define WEAPON_GRID_X 4
    #define WEAPON_GRID_Y 3

///////////////////////////////////////////////////////////////////////////////
/// \brief List of predefined creature index
///
///////////////////////////////////////////////////////////////////////////////
typedef enum creature_index_e {
    CREATURE_PLAYER,
    CREATURE_DUCK,
    CREATURE_CRAB_BOSS,
    CREATURE_BALD_RAT,
    CREATURE_ELITE_BABY_CRAB,
    CREATURE_DUMMY,
    CREATURE_CATEKILLAH,
    CREATURE_CINNAMON_RAT,
    CREATURE_BABY_CAIMAN,
    CREATURE_ELITE_RACOON,
    CREATURE_ELITE_FOX,
    CREATURE_BRAT,
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
/// \brief List of all UI's elements in the assets
///
///////////////////////////////////////////////////////////////////////////////
typedef enum ui_element_e {
    UI_FONT_ATLAS,
    UI_BUTTON_ACCEPT_IDLE,
    UI_BUTTON_ACCEPT_PRESSED,
    UI_BUTTON_BIN_DISABLED,
    UI_BUTTON_BIN_IDLE,
    UI_BUTTON_BIN_PRESSED,
    UI_BUTTON_DENY_IDLE,
    UI_BUTTON_DENY_PRESSED,
    UI_BUTTON_GENERIC_DISABLED,
    UI_BUTTON_MORE_DISABLED,
    UI_BUTTON_MORE_IDLE,
    UI_BUTTON_MORE_PRESSED,
    UI_BUTTON_NEXT_DISABLED,
    UI_BUTTON_NEXT_IDLE,
    UI_BUTTON_NEXT_PRESSED,
    UI_BUTTON_REFRESH_DISABLED,
    UI_BUTTON_REFRESH_IDLE,
    UI_BUTTON_REFRESH_PRESSED,
    UI_ELEMENT_COUNT
} ui_element_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Paths to the UI elements
///
///////////////////////////////////////////////////////////////////////////////
static const cstring_t UI_ELEMENTS_PATHS[UI_ELEMENT_COUNT] = {
    DIR_UI"/font-atlas.png",
    DIR_UI"/common/buttons/accept_idle.png",
    DIR_UI"/common/buttons/accept_pressed.png",
    DIR_UI"/common/buttons/bin_disabled.png",
    DIR_UI"/common/buttons/bin_idle.png",
    DIR_UI"/common/buttons/bin_pressed.png",
    DIR_UI"/common/buttons/deny_idle.png",
    DIR_UI"/common/buttons/deny_pressed.png",
    DIR_UI"/common/buttons/generic_disabled.png",
    DIR_UI"/common/buttons/more_disabled.png",
    DIR_UI"/common/buttons/more_idle.png",
    DIR_UI"/common/buttons/more_pressed.png",
    DIR_UI"/common/buttons/next_disabled.png",
    DIR_UI"/common/buttons/next_idle.png",
    DIR_UI"/common/buttons/next_pressed.png",
    DIR_UI"/common/buttons/refresh_disabled.png",
    DIR_UI"/common/buttons/refresh_idle.png",
    DIR_UI"/common/buttons/refresh_pressed.png"
};

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
} creature_t;

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
/// \brief Zones category type, some zone have predefined/restricted name
///
///////////////////////////////////////////////////////////////////////////////
typedef enum category_type_e {
    CAT_OTHER,
    CAT_TRAPS,
    CAT_DOORS,
    CAT_DESTRUCTIBLES,
    CATEGORY_TYPE_COUNT
} category_type_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Category structure to hold zones sub folder
///
/// \param name         The name of the category
/// \param type         The type of the category
/// \param sheets       All the assets of the category
/// \param sheetCount   The number of sheet in the category
///
///////////////////////////////////////////////////////////////////////////////
typedef struct category_s {
    cstring_t name;
    category_type_t type;
    sheet_t **sheets;
    uint_t sheetCount;
    bool_t expand;
} category_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Zone structure to hold a predefined zone
///
/// \param name         The name of the zone
/// \param categories   The list of sub folder content
/// \param categoryCount The number of categoriy
/// \param loaded       Keep track of the loaded status of the zone
///
///////////////////////////////////////////////////////////////////////////////
typedef struct zone_s {
    cstring_t name;
    category_t **categories;
    uint_t categoryCount;
    bool_t loaded;
} zone_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Vfx assets structures to hold vfx assets
///
/// \param self         The image of the vfx
/// \param name         The name of the vfx
/// \param looped       If the vfx is looped or will disapear after
/// \param background   If the vfx is drawed before the actors or not
/// \param grid         Temporary variable to parse the grid of the sprite
/// \param startingFrame The index of the first frame of the animation
/// \param endingFrame The index of the last frame of the animation
///
///////////////////////////////////////////////////////////////////////////////
typedef struct vfx_s {
    image_t *self;
    cstring_t name;
    bool_t looped;
    bool_t background;
    v2u_t grid;
    uint_t startingFrame;
    uint_t endingFrame;
} vfx_t;

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
    creature_t **creatures;
    uint_t creatureCount;
    music_t **musics;
    uint_t musicCount;
    zone_t **zones;
    uint_t zoneCount;
    vfx_t **vfx;
    uint_t vfxCount;
    image_t **weapons;
    uint_t weaponCount;
    image_t **ui;
    uint_t uiCount;
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

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize into a zone a certain category
///
/// \return True if everything initialize correctly, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_category(zone_t *zone, cstring_t path);

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize all the zones of the game, it doesn't load the assets
///
/// \return True if everything initialize correctly, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_zones(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy all zones loaded
///
///////////////////////////////////////////////////////////////////////////////
void destroy_assets_zones(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy one category of zone
///
///////////////////////////////////////////////////////////////////////////////
void destroy_assets_category(category_t *cat);

///////////////////////////////////////////////////////////////////////////////
/// \brief Sort the creatures by their id
///
///////////////////////////////////////////////////////////////////////////////
void sort_creatures(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy all the assets
///
///////////////////////////////////////////////////////////////////////////////
void destroy_assets(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Search a music
///
/// \param name         The name of the music
///
/// \return Pointer to the sfMusic element or NULL if not found
///
///////////////////////////////////////////////////////////////////////////////
sfMusic *find_music(cstring_t name);

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize all the VFX assets
///
/// \return True if everything is loaded, False otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_vfx(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy all the loaded VFX assets and set the values back to 0
///
///////////////////////////////////////////////////////////////////////////////
void destroy_assets_vfx(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize every weapons assets
///
/// \return True if everything works fines, false otherwise (To many or few
/// weapon found in the folder)
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_weapons(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy every weapon assets
///
///////////////////////////////////////////////////////////////////////////////
void destroy_assets_weapons(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy every images once created in the engine
///
///////////////////////////////////////////////////////////////////////////////
void destroy_all_images(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Load every assets of the interface
///
/// \return True if everything is loaded, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_ui(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy every interface assets
///
///////////////////////////////////////////////////////////////////////////////
void destroy_assets_ui(void);

#endif /* !ASSETS_H_ */
