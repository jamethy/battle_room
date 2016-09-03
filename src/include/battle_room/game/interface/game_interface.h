#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "battle_room/engine/animation/view_interface.h"

namespace BattleRoom {

class GameInterface : public ViewInterface {

public:

    // inherited
    std::vector<Object> getObjects() override; 
    std::vector<DrawableText> getDrawableTexts() override;
    Inputs handleInputs(Inputs inputs) override;
    void applySettings(ResourceDescriptor settings) override;

private:

}; // GameInterface class
} // BattleRoom namespace
#endif // GAME_INTERFACE_H
