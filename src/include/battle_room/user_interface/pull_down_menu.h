#ifndef PULL_DOWN_MENU_H
#define PULL_DOWN_MENU_H

#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    class PullDownMenu : public Menu {

        public:

            PullDownMenu();

            std::vector<DrawableText> getDrawableTexts() override;
            std::vector<DrawableMenu> getDrawableMenus() override;
            bool handleInput(Input input, RelPixel point) override;
            void updateAnimation(seconds timestep) override;

            void applySettings(ResourceDescriptor settings) override;

        private:
            DrawableMenu m_pullDown;

    }; // Menu Class
} // BattleRoom namespace
#endif // PULL_DOWN_MENU_H

