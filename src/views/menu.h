#ifndef BATTLE_ROOM_BATTLEROOM_MENU_H
#define BATTLE_ROOM_BATTLEROOM_MENU_H

#include "display_window/drawable_menu.h"
#include "common/unique_id.h"
#include "application/input.h"

namespace BattleRoom {

    class Menu : public Resource {

        public:

            Menu(UniqueId menuId);

            virtual bool handleInput(Input input, RelPixel point) = 0;

            virtual void updateAnimation(seconds timestep) = 0;

            virtual std::vector<DrawableMenu> getDrawableMenus() = 0;

            UniqueId getUniqueId();

        protected:

            bool objectBoundaryContains(const DrawableMenu& obj, RelPixel point);

            UniqueId m_uniqueId;

    }; // Menu Class

    typedef std::unique_ptr<Menu> UniqueMenu;

} // BattleRoom namespace
#endif // BATTLE_ROOM_BATTLEROOM_MENU_H
