#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "battle_room/common/drawable_object.h"
#include "battle_room/common/unique_id.h"

namespace BattleRoom {

class GameObject : public DrawableObject {

public:

    // constructor
    GameObject(UniqueId uniqueId);


    // getters and setters

    const UniqueId getUniqueId() const;
    Vector3D getVelocity();
    bool isStatic() const;


    // inherited 

    virtual void applySettings(ResourceDescriptor settings) override;

private:

    UniqueId m_uniqueId; ///< Object's uniqueId
    Vector3D m_velocity; ///< Object's velocity
    bool m_isStatic; ///< If object is static, it does not move or intersect other static objects

}; // GameObject class
} // BattleRoom namespace
#endif // GAME_OBJECT_H
