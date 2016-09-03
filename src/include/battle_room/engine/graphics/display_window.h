#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "battle_room/common/object.h"
#include "battle_room/common/drawable_text.h"
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
     * \breif Collects window inputs to the InputGatherer
     * This should be called after every window as been drawn
     */
    virtual void gatherInputs() = 0;
    
    /*!
     * \brief Sets the objects that need to be rendered
     * If view not found, nothing is done
     * \param objects Objects that will be drawn on the view
     * \param viewName Key to find view to draw on
     */
    virtual void setViewObjects(std::vector<Object> objects, std::string viewName) = 0;

    /*!
     * \brief Sets the drawable text to the view to be rendered
     * If view not found, nothing is done
     * \param texts List of texts to be drawn on the view
     * \param viewName Key to find view to draw on
     */
    virtual void setViewTexts(std::vector<DrawableText> texts, std::string viewName) = 0;

    /*!
     * \brief Draws the world, UI, and then menu objects
     */
    virtual void drawScreen() = 0;

    /*!
     * \brief Addes a view to the display window
     * \TODO add a remove view
     */
    virtual void addView(View view) = 0;

    /**
     * \brief Handles inputs - such as for cameras
     * \param inputs Inputs to handle
     * \return Any inputs remaining after using the param
     */
    virtual Inputs handleInputs(Inputs inputs) = 0;

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
