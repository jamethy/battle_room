#include "battle_room/user_interface/game_interface.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

using std::vector;

namespace BattleRoom {

// apply settings

void GameInterface::applySettings(ResourceDescriptor settings) {

    ViewInterface::applySettings(settings);

}

// constructors

GameInterface::GameInterface(ResourceDescriptor settings)
{ 
    applySettings(settings);
}

// other functions

vector<DrawableObject> GameInterface::getDrawableObjects() {

    vector<DrawableObject> objects;
    objects.clear();


    for (GameObject& obj : QueryWorld::getAllGameObjects()) {
        objects.push_back(obj);
    }
    return objects;
}

vector<DrawableText> GameInterface::getDrawableTexts() {
    return vector<DrawableText>();
}

Inputs GameInterface::handleInputs(Inputs inputs) {

    Inputs remainingInputs;

    for (Input input : inputs) {

        if (input.containsView(getAssociatedView())) {

            if (input.getMotion() == InputKey::Motion::PressedDown) {
                if (input.getKey() == InputKey::Key::Q) {
                    InputGatherer::addQuitEvent();
                }
            }

        }

        remainingInputs.addInput(input);
    }

    // CommandReceiver::addCommands

    return remainingInputs;
}

} // BattleRoom namespace
