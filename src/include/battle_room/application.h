#ifndef BATTLE_ROOM_APPLICATION_H
#define BATTLE_ROOM_APPLICATION_H

#include "battle_room/common/resource.h"
#include "battle_room/common/view_interface.h"
#include "battle_room/common/application_message.h"
#include "battle_room/game/query_world_updater.h"
#include "battle_room/graphics/display_window.h"

#include <map>

namespace BattleRoom {

    class Application : Resource {

    public:

        Application(ResourceDescriptor settings);

        void runApplicationLoop();

        void applySettings(ResourceDescriptor settings) override;

    private:

        void addResource(ResourceDescriptor settings);
        void modifyResource(UniqueId target, ResourceDescriptor settings);
        void removeResource(UniqueId target);
        void applyMessage(ApplicationMessage message);

        void addWindow(ResourceDescriptor settings);
        void addViewTo(UniqueId windowId, ResourceDescriptor settings);
        bool removeWindow(UniqueId windowId);
        bool removeView(UniqueId viewId);

        std::map<UniqueId, std::vector<UniqueInterface>> m_viewMap;
        std::vector<UniqueDisplayWindow> m_windows;
        //std::vector<UniqueInterface> m_viewInterfaces;

        UniqueWorldUpdater m_worldUpdater;

    }; // GameInterface class
} // BattleRoom namespace
#endif // BATTLE_ROOM_APPLICATION_H

