#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#include "battle_room/common/view_interface.h"
#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    class MenuInterface : public ViewInterface {

        public:

            MenuInterface(ResourceDescriptor settings, UniqueId viewId);

            // inherited
            std::vector<DrawableObject> getDrawableObjects() override;

            std::vector<DrawableText> getDrawableTexts() override;

            std::vector<DrawableMenu> getDrawableMenus() override;

            Inputs handleInputs(Inputs inputs) override;

            std::vector<ResourceDescriptor> getNewSettings() override;

            void applySettings(ResourceDescriptor settings) override;

        private:

            std::vector<UniqueMenu> m_menus;

    }; // MenuInterface class
} // BattleRoom namespace
#endif // MENU_INTERFACE_H

