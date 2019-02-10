#include <common/logger.h>
#include "views/interface_factory.h"
#include "views/game_interface.h"
#include "views/menu_interface.h"

namespace BattleRoom {

    UniqueInterface InterfaceFactory::createInterface(ResourceDescriptor settings, DisplayWindow* displayWindow, Application* application) {

        auto interfaceType = settings.getSubResource("Type").getValue();

        if (keyMatch("Menu", interfaceType)) {
            return UniqueInterface(new MenuInterface(
                    settings,
                    displayWindow->getTextureManager(),
                    displayWindow->getWidth(),
                    displayWindow->getHeight(),
                    application
            ));
        } else if (keyMatch("Game", interfaceType)) {
            return UniqueInterface(new GameInterface(
                    settings,
                    displayWindow->getTextureManager(),
                    displayWindow->getWidth(),
                    displayWindow->getHeight()
            ));
        } else {
            Log::error("Unrecgonized interface type: ", interfaceType);
            return nullptr;
            // TODO create a blank interface
        }
    }

} // BattleRoom namespace

