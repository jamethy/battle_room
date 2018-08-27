#ifndef PULL_DOWN_MENU_H
#define PULL_DOWN_MENU_H

#include "menu.h"
#include "application_message.h"

namespace BattleRoom {

    class PullDownMenu : public Menu {

        public:

            PullDownMenu(UniqueId menuId);

            //getters and setters
            std::vector<ApplicationMessage> getOnClick() const;
            void setOnClick(std::vector<ApplicationMessage> messages);

            // inherited
            std::vector<DrawableText> getDrawableTexts() override;
            std::vector<DrawableMenu> getDrawableMenus() override;
            bool handleInput(Input input, RelPixel point) override;
            void updateAnimation(seconds timestep) override;

            void applySettings(ResourceDescriptor settings) override;

        private:
            std::vector<ApplicationMessage> m_onClick;
            DrawableMenu m_pullDown;

    }; // Menu Class
} // BattleRoom namespace
#endif // PULL_DOWN_MENU_H

