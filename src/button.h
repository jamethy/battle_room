#ifndef BUTTON_H
#define BUTTON_H

#include "menu.h"
#include "application_message.h"

namespace BattleRoom {

    class Button : public Menu {

        public:

            Button(UniqueId menuId);

            //getters and setters
            std::vector<ApplicationMessage> getOnClick() const;
            void setOnClick(std::vector<ApplicationMessage> messages);

            std::vector<DrawableText> getDrawableTexts() override;
            std::vector<DrawableMenu> getDrawableMenus() override;
            bool handleInput(Input input, RelPixel point) override;
            void updateAnimation(seconds timestep) override;

            void applySettings(ResourceDescriptor settings) override;
        private:

            DrawableMenu m_button;
            std::vector<ApplicationMessage> m_onClick;
            bool m_buttonDown;

    }; // Menu Class
} // BattleRoom namespace
#endif // BUTTON_H


