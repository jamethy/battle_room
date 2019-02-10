#ifndef BATTLE_ROOM_INTERFACE_FACTORY_H
#define BATTLE_ROOM_INTERFACE_FACTORY_H

#include "views/view_interface.h"
#include "display_window/display_window.h"
#include "application/application.h"

namespace BattleRoom {

    /**
     * Static class for creating View Interfaces
     */
    class InterfaceFactory {

    public:

        /**
         * \brief creates a view interface using the settings given
         * \param settings descriptor of the view to be created (value Game or Menu)
         * \param windowWidth Width of window view is being created for
         * \param windowHeight Height of window view is being created for
         * \return Unique pointer to view interface
         */
        static UniqueInterface createInterface(ResourceDescriptor settings, DisplayWindow* displayWindow, Application* application);

    }; // InterfaceFactory class
} // BattleRoom namespace
#endif // BATTLE_ROOM_INTERFACE_FACTORY_H

