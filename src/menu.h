#ifndef BATTLEROOM_MENU_H
#define BATTLEROOM_MENU_H

#include "drawable_text.h"
#include "drawable_menu.h"
#include "unique_id.h"
#include "input.h"

namespace BattleRoom {

    class Menu : public Resource {

        public:

            Menu(UniqueId menuId);

            virtual bool handleInput(Input input, RelPixel point) = 0;

            virtual void updateAnimation(seconds timestep) = 0;

            virtual std::vector<DrawableText> getDrawableTexts() = 0;

            virtual std::vector<DrawableMenu> getDrawableMenus() = 0;

            UniqueId getUniqueId();

        protected:

            bool objectBoundaryContains(const DrawableMenu& obj, RelPixel point);

            UniqueId m_uniqueId;

    }; // Menu Class

    typedef std::unique_ptr<Menu> UniqueMenu;

} // BattleRoom namespace
#endif // BATTLEROOM_MENU_H
