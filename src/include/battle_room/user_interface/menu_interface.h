#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#include "battle_room/user_interface/view.h"
#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    class MenuInterface : public View {

        public:

            MenuInterface(ResourceDescriptor settings, int windowWidth, int windowHeight);

            // inherited
            std::vector<DrawableObject> getDrawableObjects() override;

            std::vector<DrawableText> getDrawableTexts() override;

            std::vector<DrawableMenu> getDrawableMenus() override;

            void update(seconds timestep) override;

            Inputs handleInputs(Inputs inputs) override;

            void applySettings(ResourceDescriptor settings) override;

        private:

            std::vector<UniqueMenu> m_menus;

    }; // MenuInterface class
} // BattleRoom namespace
#endif // MENU_INTERFACE_H

