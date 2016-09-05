#include "battle_room/game/interface/game_interface.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/engine/animation/animation_handler.h"
#include <iostream>

using std::vector;

namespace BattleRoom {

vector<Object> GameInterface::getObjects() {
    vector<Object> objects;
    objects.clear();
    return objects;
}

vector<DrawableText> GameInterface::getDrawableTexts() {
    return vector<DrawableText>();
}

Inputs GameInterface::handleInputs(Inputs inputs) {

    Inputs remainingInputs;

    for (Input input : inputs) {

        if (input.containsView(getAssociatedView())) {
            

        }

        remainingInputs.addInput(input);
    }


    return remainingInputs;
}

void GameInterface::applySettings(ResourceDescriptor settings) {

}

} // BattleRoom namespace
