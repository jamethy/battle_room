#include "interface_factory.h"
#include "game_interface.h"
#include "menu_interface.h"

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
                    displayWindow->getWidth(),
                    displayWindow->getHeight()
            ));
        }

        // TODO create a blank interface
    }

} // BattleRoom namespace

