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


    // inherited 

    virtual void applySettings(ResourceDescriptor settings) override;

private:

    UniqueId m_uniqueId; ///< Objects uniqueId

}; // GameObject class
} // BattleRoom namespace
#endif // GAME_OBJECT_H
