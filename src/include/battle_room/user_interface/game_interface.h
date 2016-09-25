#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "battle_room/common/view_interface.h"
#include "battle_room/game/world.h"

namespace BattleRoom {

class GameInterface : public ViewInterface {

public:

    GameInterface(ResourceDescriptor settings);

    // inherited
    std::vector<DrawableObject> getDrawableObjects() override; 
    std::vector<DrawableText> getDrawableTexts() override;
    Inputs handleInputs(Inputs inputs) override;
    std::vector<ResourceDescriptor> getNewSettings() override;
    void applySettings(ResourceDescriptor settings) override;

private:

    UniqueId m_idToTrack; ///< Tracks the given unique id

}; // GameInterface class
} // BattleRoom namespace
#endif // GAME_INTERFACE_H
