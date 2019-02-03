
#ifndef BATTLE_ROOM_GAME_UI_ELEMENT_H
#define BATTLE_ROOM_GAME_UI_ELEMENT_H

#include "units.h"
#include "vector3d.h"
#include "quaternion.h"
#include "unique_id.h"

namespace BattleRoom {

    class GameUIElement : public Resource {
    public:

        GameUIElement();

        virtual std::string getType() const = 0;

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
#endif //PROJECT_BATTLE_ROOM_GAMEUIELEMENT_H
