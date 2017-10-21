#ifndef BATTLEROOM_MENU_H
#define BATTLEROOM_MENU_H

#include "battle_room/common/drawable_text.h"
#include "battle_room/common/drawable_menu.h"
#include "battle_room/common/unique_id.h"

namespace BattleRoom {

    class Menu {

        public:

            Menu();

            bool contains(RelPixel point);

            std::vector<DrawableText> getDrawableTexts();

            std::vector<DrawableMenu> getDrawableMenus();

            UniqueId getUniqueId();

        protected:

            std::vector<DrawableText> m_texts;
            std::vector<DrawableMenu> m_menus;
            UniqueId m_uniqueId;

    }; // Menu Class

    typedef std::unique_ptr<Menu> UniqueMenu;

} // BattleRoom namespace
#endif // BATTLEROOM_MENU_H
