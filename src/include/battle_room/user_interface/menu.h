#ifndef BATTLEROOM_MENU_H
#define BATTLEROOM_MENU_H

#include "battle_room/common/drawable_text.h"
#include "battle_room/common/drawable_menu.h"

namespace BatteRoom {

    class Menu {

        public:

            std::vector<DrawableText> getDrawableTexts();

            std::vector<DrawableMenu> getDrawableMenus();

        private:

            // container
            // text displays
            // buttons

    }; // Menu Class
} // BattleRoom namespace
#endif // BATTLEROOM_MENU_H
