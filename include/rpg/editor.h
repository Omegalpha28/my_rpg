/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** editor
*/

#ifndef EDITOR_H_
    #define EDITOR_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Editor scene enumeration
///
///////////////////////////////////////////////////////////////////////////////
typedef enum editor_scene_e {
    editorSceneZoneSelection,
    editorSceneCreation,
    editorSceneSaving,
    EDITOR_SCENE_COUNT
} editor_scene_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Editor structure to keep every data needed for the level-editor
///
/// \param fProps       Props array of the foreground
/// \param fCount       The number of props in the foreground
/// \param fDisplay     Is the foreground displayed
/// \param bProps       Props array of the background
/// \param bcount       The number of props in the background
/// \param bDisplay     Is the background displayed
/// \param focus        The prop currently focused
/// \param hover        Is the focused prop hovered
/// \param dragging     Is the user currently dragging the focused prop
/// \param zoneId       The current loaded zone id
/// \param zone         The current loaded zone pointer
/// \param oldMouse     The previous mouse position
/// \param crtMouse     The current mouse position
///
///////////////////////////////////////////////////////////////////////////////
extern struct editor_s {
    editor_scene_t scene;
    prop_t **fProps;
    uint_t fCount;
    bool_t fDisplay;
    prop_t **bProps;
    uint_t bCount;
    bool_t bDisplay;
    prop_t *focus;
    bool_t hover;
    bool_t dragging;
    int zoneId;
    zone_t *zone;
    v2f_t oldMouse;
    v2f_t crtMouse;
} Editor;

///////////////////////////////////////////////////////////////////////////////
/// \brief Main loop of the level editor
///
///////////////////////////////////////////////////////////////////////////////
void editor_loop(void);

#endif /* !EDITOR_H_ */
