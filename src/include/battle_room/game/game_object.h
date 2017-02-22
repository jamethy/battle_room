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
    kilograms getMass() const;
    std::string getName() const;

    void setVelocity(Vector3D velocity);
    void setIsStatic(bool isStatic);
    void setMass(kilograms mass);
    void setName(std::string name);

    // inherited 

    virtual void applySettings(ResourceDescriptor settings) override;

private:

    UniqueId m_uniqueId; ///< Object's uniqueId
    Vector3D m_velocity; ///< Object's velocity
    bool m_isStatic; ///< If object is static, it does not move or intersect other static objects
    kilograms m_mass; ///< mass in kilograms of the object
    std::string m_name; ///< label used for debugging

}; // GameObject class
} // BattleRoom namespace
#endif // GAME_OBJECT_H
