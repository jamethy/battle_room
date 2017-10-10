#include "battle_room/user_interface/spatial_element.h"
#include "battle_room/common/animation_handler.h"

namespace BattleRoom {


    SpatialElement::SpatialElement(UniqueId focus) :
        m_focus(focus)
    {
        setAnimation(AnimationHandler::getAnimation("spatial/selected"));
    }

    void SpatialElement::update(std::vector<GameObject*>& objects) {
        for (GameObject* obj : objects) {
            if (obj->getUniqueId() == m_focus) {
                Vector3D loc = obj->getLocation();
                setLocation(Vector3D(loc.x(), loc.y(), -0.1));
                break;
            }
        }
    }
}
