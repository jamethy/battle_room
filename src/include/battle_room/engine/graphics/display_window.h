#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "battle_room/common/object.h"
#include "battle_room/common/inputs.h"
#include "battle_room/common/resource_descriptor.h"
#include "battle_room/engine/animation/view.h"
#include "battle_room/engine/graphics/texture_manager.h"

#include <vector>
#include <memory>

namespace BattleRoom {

class DisplayWindow {

public:

    //virtual void applySettings(ResourceDescriptor settings);

    /*!
     * Returns the collection of user inputs that have been gathered
     */
    virtual Inputs getInputs() = 0;
    
    /*!
     * Add the game world objects that need to be rendered
     */
    virtual void addObjectsToView(std::vector<Object> objects, std::string viewName) = 0;

    /*!
     * Draws the world, UI, and then menu objects
     */
    virtual void drawScreen() = 0;

    virtual TextureManager& getTextureManager() = 0;

    virtual void addView(View view) = 0;

}; // DisplayWindow class

/*!
 * Creates a display window
 */
typedef std::unique_ptr<DisplayWindow> UniqueDisplayWindow;
UniqueDisplayWindow createDisplayWindow(ResourceDescriptor descriptor);

} // BattleRoom namespace
#endif // DISPLAY_WINDOW_H
