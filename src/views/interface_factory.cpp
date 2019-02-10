#include "views/interface_factory.h"
#include "views/game_interface.h"
#include "views/menu_interface.h"

namespace BattleRoom {

    UniqueInterface InterfaceFactory::createInterface(ResourceDescriptor settings, DisplayWindow* displayWindow, Application* application) {

        if (keyMatch("Menu", settings.getValue())) {
            return UniqueInterface(new MenuInterface(
                    settings,
                    displayWindow->getTextureManager(),
                    displayWindow->getWidth(),
                    displayWindow->getHeight(),
                    application
            ));
        } else {
            return UniqueInterface(new GameInterface(
                    settings,
                    displayWindow->getTextureManager(),
                    displayWindow->getWidth(),
                    displayWindow->getHeight()
            ));
        }

        // TODO create a blank interface
    }

} // BattleRoom namespace

