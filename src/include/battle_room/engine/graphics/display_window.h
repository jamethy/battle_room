#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "battle_room/common/object.h"
#include "battle_room/common/inputs.h"
#include "battle_room/engine/graphics/texture_manager.h"

#include <vector>
#include <memory>

namespace BattleRoom {

class DisplayWindow {

public:

    /*!
     * Returns the collection of user inputs that have been gathered
     */
    virtual Inputs getInputs() = 0;
    
    /*!
     * Add the game world objects that need to be rendered
     */
    virtual void addWorldObjects(std::vector<Object> objects) = 0;

    /*!
     * Add the UI objects that need to be rendered
     */
    virtual void addUiObjects(std::vector<Object> objects) = 0;

    /*!
     * Add the Menu objects that need to be rendered
     */
    virtual void addMenuObjects(std::vector<Object> objects) = 0;

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

} // BattleRoom namespace
#endif // DISPLAY_WINDOW_H
