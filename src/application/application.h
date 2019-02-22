#ifndef BATTLE_ROOM_APPLICATION_H
#define BATTLE_ROOM_APPLICATION_H

#include "common/resource.h"
#include "views/view_interface.h"
#include "application/application_message.h"
#include "world/query_world_updater.h"
#include "display_window/display_window.h"
#include "networking/server_connection.h"

#include <map>

namespace BattleRoom {

    /**
     * \brief Main class the application runs from. Internally accepts
     * application messages and runs application loop.
     */
    class Application : public Resource {

    public:

        // constructor
        explicit Application(ResourceDescriptor settings);

        ~Application() override;

        /**
         * \brief main application loop
         *
         * Does the following until an application message quit event is received
         *  - gathers inputs from windows
         *  - views handle inputs
         *  - update query world buffer
         *  - copy drawables from views to windows
         *  - draw screen
         *  - handle application messages
         */
        void runApplicationLoop();

        static int initializeWeb(int argc, char **argv);

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        // adds a resource from settings
        void addResource(ResourceDescriptor settings);

        // modifies a resource with uniqueId target by using settings
        void modifyResource(UniqueId target, ResourceDescriptor settings);

        // removes a resource with uniqueId target
        void removeResource(UniqueId target);

        // apply application message to application
        void applyMessage(ApplicationMessage message);

        void updateApplicationState();

        // add window using settings - and adds to m_viewMap
        void addWindow(ResourceDescriptor settings);

        void addInterface(ResourceDescriptor settings);

        // add view using settings to the window with given uniqueId
        void addViewTo(UniqueId windowId, ResourceDescriptor settings);

        // remove the window with the given id
        bool removeWindow(UniqueId windowId);

        // remove the view with the given id
        bool removeView(UniqueId viewId);

        std::vector<UniqueDisplayWindow> m_windows; ///< app windows
        std::map<UniqueId, std::vector<UniqueInterface>> m_viewMap; ///< map of window Id to list of views

        UniqueWorldUpdater m_worldUpdater; ///< query world updater

    }; // GameInterface class
} // BattleRoom namespace
#endif // BATTLE_ROOM_APPLICATION_H

