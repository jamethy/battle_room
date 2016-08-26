#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "battle_room/common/object.h"
#include "battle_room/common/inputs.h"
#include "battle_room/common/resource.h"
#include "battle_room/engine/animation/view.h"
#include "battle_room/engine/animation/camera.h"

#include <vector>
#include <unordered_map>
#include <memory>

namespace BattleRoom {

/**
 * \brief Window that displays graphics
 * Has views that represent portions of the screen and objects within the views
 * that are drawable
 */
class DisplayWindow : public Resource {

public:

    // destructor
    virtual ~DisplayWindow(){};

    /*!
     * \breif Returns the collection of user inputs that have been gathered
     * \return Inputs class containing user input information
     */
    virtual Inputs getInputs() = 0;
    
    /*!
     * \brief Add the game world objects that need to be rendered
     * \param objects Objects that will be drawn on the view
     * \param viewName Key to find view to draw on
     */
    virtual void addObjectsToView(std::vector<Object> objects, std::string viewName) = 0;

    /*!
     * \brief Draws the world, UI, and then menu objects
     */
    virtual void drawScreen() = 0;

    /*!
     * \brief Addes a view to the display window
     * \TODO add a remove view
     */
    virtual void addView(View view) = 0;

    /*!
     * \brief Sets the reference to the camera map
     * \param cameraMap Map of camera objects to their names
     */
    virtual void setCameraMapReference(std::unordered_map<std::string,Camera>& cameraMap) = 0;

}; // DisplayWindow class

// Window Pointer that will delete itself
typedef std::unique_ptr<DisplayWindow> UniqueDisplayWindow;

/*!
 * \brief Creates a display window
 * \param Resource descriptor describing the window to be created
 * \return Unique Pointer to the window that was created
 */
UniqueDisplayWindow createDisplayWindow(ResourceDescriptor descriptor);

} // BattleRoom namespace
#endif // DISPLAY_WINDOW_H
