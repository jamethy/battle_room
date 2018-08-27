#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#include "view.h"
#include "menu.h"

namespace BattleRoom {

    /**
     * \brief View impl for displaying a menu
     */
    class MenuInterface : public View {

        public:

            // constructor
            MenuInterface(ResourceDescriptor settings, int windowWidth, int windowHeight);

            // inherited
            std::vector<DrawableObject> getDrawableObjects() override;
            std::vector<DrawableText> getDrawableTexts() override;
            std::vector<DrawableMenu> getDrawableMenus() override;
            void update(seconds timestep) override;
            Inputs handleInputs(Inputs inputs) override;
            void applySettings(ResourceDescriptor settings) override;

        private:

            std::vector<UniqueMenu> m_menus; ///< menus to draw

    }; // MenuInterface class
} // BattleRoom namespace
#endif // MENU_INTERFACE_H

