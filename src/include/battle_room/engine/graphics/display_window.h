#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "battle_room/common/object.h"
#include "battle_room/common/inputs.h"
#include "battle_room/engine/graphics/texture_manager.h"

#include <vector>
#include <memory>

namespace Graphics {

class DisplayWindow {

public:

    /*!
     * Returns the collection of user inputs that have been gathered
     */
    virtual Common::Inputs getInputs() = 0;
    
    /*!
     * Add the game world objects that need to be rendered
     */
    virtual void addWorldObjects(std::vector<Common::Object> objects) = 0;

    /*!
     * Add the UI objects that need to be rendered
     */
    virtual void addUiObjects(std::vector<Common::Object> objects) = 0;

    /*!
     * Add the Menu objects that need to be rendered
     */
    virtual void addMenuObjects(std::vector<Common::Object> objects) = 0;

    /*!
     * Draws the world, UI, and then menu objects
     */
    virtual void drawScreen() = 0;

    virtual TextureManager& getTextureManager() = 0;

}; // DisplayWindow class

/*!
 * Creates a display window
 */
typedef std::unique_ptr<DisplayWindow> UniqueDisplayWindow;
UniqueDisplayWindow createDisplayWindow(std::string settingsFilename);

} // Graphics namespace
#endif // DISPLAY_WINDOW_H