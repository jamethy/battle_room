#ifndef BUTTON_H
#define BUTTON_H

#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    class Button : public Menu {

        public:

            Button();

            std::vector<DrawableText> getDrawableTexts() override;
            std::vector<DrawableMenu> getDrawableMenus() override;
            bool handleInput(Input input, RelPixel point) override;
            void updateAnimation(seconds timestep) override;

            void applySettings(ResourceDescriptor settings) override;
        private:

            DrawableMenu m_button;

    }; // Menu Class
} // BattleRoom namespace
#endif // BUTTON_H


