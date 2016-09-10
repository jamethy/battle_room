#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "battle_room/engine/animation/view_interface.h"
#include "battle_room/game/world/game_world.h"

namespace BattleRoom {

class GameInterface : public ViewInterface {

public:

    GameInterface(GameWorld& gameWorld, ResourceDescriptor settings);

    // inherited
    std::vector<DrawableObject> getDrawableObjects() override; 
    std::vector<DrawableText> getDrawableTexts() override;
    Inputs handleInputs(Inputs inputs) override;
    void applySettings(ResourceDescriptor settings) override;

private:

    GameWorld& m_gameWorld;

}; // GameInterface class
} // BattleRoom namespace
#endif // GAME_INTERFACE_H
