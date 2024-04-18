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
/// \param copy         The prop currently copied
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
    prop_t *copy;
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

///////////////////////////////////////////////////////////////////////////////
/// \brief Handle all the events of the level editor windows
///
/// \param evt          The current event
///
///////////////////////////////////////////////////////////////////////////////
void handle_editor_events(sfEvent evt);

///////////////////////////////////////////////////////////////////////////////
/// \brief Create and add a new prop to the foreground or background layer
/// of the editor
///
/// \param sheet        The sheet reference to create the prop
/// \param array        The array of props (background/foreground)
/// \param count        The counter of props in the array
///
///////////////////////////////////////////////////////////////////////////////
void add_prop(sheet_t *sheet, prop_t ***array, uint_t *count);

///////////////////////////////////////////////////////////////////////////////
/// \brief Search in all the props to apply the focus
///
/// \param evt          The mouse button event
///
///////////////////////////////////////////////////////////////////////////////
void search_for_focus(sfMouseButtonEvent evt);

///////////////////////////////////////////////////////////////////////////////
/// \brief Search in a list of props if the mouse is on one of it
///
/// \param isDisplayed  Boolean is the layer displayed
/// \param propCount    The number of prop in the array of props
/// \param props        The array of props of one layer
///
/// \return True if the mouse is over a prop, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t search_in_props(bool_t isDisplayed, uint_t propCount, prop_t **props);

///////////////////////////////////////////////////////////////////////////////
/// \brief Get the prop boundary
///
/// \param prop         Pointer to the desired prop
///
/// \return The boundary of the prop
///
///////////////////////////////////////////////////////////////////////////////
recti_t get_prop_bound(prop_t *prop);

///////////////////////////////////////////////////////////////////////////////
/// \brief Handle click on the level editor
///
/// \param evt          The mouse button event to parse
///
///////////////////////////////////////////////////////////////////////////////
void handle_editor_mouse_button(sfMouseButtonEvent evt);

///////////////////////////////////////////////////////////////////////////////
/// \brief Parse and handle differents event when scrolling on the canvas.
/// Zoom or move on the canvas (ALT/CTRL)
///
/// \param evt          The mouse scroll event
///
///////////////////////////////////////////////////////////////////////////////
void handle_editor_mouse_scroll(sfMouseWheelScrollEvent evt);

///////////////////////////////////////////////////////////////////////////////
/// \brief Handle the mouse movement on the windows
///
///////////////////////////////////////////////////////////////////////////////
void handle_mouse_move(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Handle the keyboard pressed/released event
///
/// \param evt          The key event to handle
///
///////////////////////////////////////////////////////////////////////////////
void handle_editor_key_pressed(sfKeyEvent evt);

#endif /* !EDITOR_H_ */
