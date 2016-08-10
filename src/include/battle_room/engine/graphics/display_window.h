#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "battle_room/common/object.h"
#include "battle_room/common/inputs.h"

#include <vector>

namespace Graphics {

class DisplayWindow {

public:

    /*!
     * Returns the collection of user inputs that have been gathered
     */
    Common::Inputs getInputs();
    
    /*!
     * Add the game world objects that need to be rendered
     */
    void addWorldObjects(std::vector<Common::Object> objects);

    /*!
     * Add the UI objects that need to be rendered
     */
    void addUiObjects(std::vector<Common::Object> objects);

    /*!
     * Add the Menu objects that need to be rendered
     */
    void addMenuObjects(std::vector<Common::Object> objects);

    /*!
     * Draws the world, UI, and then menu objects
     */
    void drawScreen();

protected:

    // made it protected so it can't be created
    DisplayWindow();

}; // DisplayWindow class

/*!
 * Creates a display window
 */
DisplayWindow* createDisplayWindow(std::string settingsFilename);

} // Graphics namespace
#endif // DISPLAY_WINDOW_H
