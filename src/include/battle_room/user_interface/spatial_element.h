#ifndef SPATIAL_ELEMENT_H
#define SPATIAL_ELEMENT_H

#include "battle_room/common/drawable_object.h"
#include "battle_room/game/game_object.h"

namespace BattleRoom {

    class SpatialElement : public DrawableObject {

        public:
            SpatialElement(UniqueId focus);

            void update(std::vector<GameObject*>& objects);

        private:
            UniqueId m_focus;

    }; // SpatialElement class

} // BattleRoom namespace 
#endif // SPATIAL_ELEMENT_H

