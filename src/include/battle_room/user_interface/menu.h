#ifndef BATTLEROOM_MENU_H
#define BATTLEROOM_MENU_H

#include "battle_room/common/drawable_text.h"
#include "battle_room/common/drawable_menu.h"
#include "battle_room/common/unique_id.h"
#include "battle_room/common/input.h"

namespace BattleRoom {

    class Menu {

        public:

            Menu();

            virtual bool handleInput(Input input, RelPixel point) = 0;

            virtual void updateAnimation(seconds timestep) = 0;

            virtual std::vector<DrawableText> getDrawableTexts() = 0;

            virtual std::vector<DrawableMenu> getDrawableMenus() = 0;

            UniqueId getUniqueId();

        protected:

            bool objectBoundaryContains(const DrawableMenu& menu, RelPixel point);

            UniqueId m_uniqueId;

    }; // Menu Class

    typedef std::unique_ptr<Menu> UniqueMenu;

} // BattleRoom namespace
#endif // BATTLEROOM_MENU_H
