
#ifndef BATTLE_ROOM_GAME_UI_ELEMENT_H
#define BATTLE_ROOM_GAME_UI_ELEMENT_H

#include "common/units.h"
#include "common/vector3d.h"
#include "common/quaternion.h"
#include "common/unique_id.h"
#include "views/view.h"

namespace BattleRoom {

    class GameUIElement : public Resource {
    public:

        GameUIElement();

        virtual std::string getType() const = 0;

        virtual std::string getJson(Camera* camera, View* view) const = 0;

        // getters and setters

        UniqueId getUniqueId() const;

        Vector3D getLocation() const;

        void setLocation(const Vector3D &location);

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        UniqueId m_uniqueId;

        Vector3D m_location; ///< Location of the object in 3D space

    };//GameUIElement class
}// BattleRoom namespace
#endif //BATTLE_ROOM_GAME_UI_ELEMENT_H
