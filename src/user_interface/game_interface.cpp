#include "battle_room/user_interface/game_interface.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"
#include <iostream>

using std::vector;

namespace BattleRoom {

// apply settings

    void GameInterface::applySettings(ResourceDescriptor settings) {

        ViewInterface::applySettings(settings);

    }

// constructors

    GameInterface::GameInterface(ResourceDescriptor settings)
            : m_idToTrack(UniqueId::generateInvalidId()) {
        applySettings(settings);
    }

// other functions

    vector<DrawableObject> GameInterface::getDrawableObjects() {

        vector<DrawableObject> objects;
        objects.clear();


        for (GameObject *obj : QueryWorld::getAllGameObjects()) {
            objects.push_back(DrawableObject(*obj));
        }
        return objects;
    }

    vector<DrawableText> GameInterface::getDrawableTexts() {
        return vector<DrawableText>();
    }

    Inputs GameInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;


        for (Input input : inputs) {

            // temp for easy testing and quitting
            if (input.getMotion() == InputKey::Motion::PressedDown) {
                if (input.getKey() == InputKey::Key::Q) {
                    InputGatherer::addQuitEvent();
                }
            }

            if (input.containsView(getAssociatedView())) {

            }

            remainingInputs.addInput(input);
        }

        // CommandReceiver::addCommands

        return remainingInputs;
    }

    vector<ResourceDescriptor> GameInterface::getNewSettings() {
        vector<ResourceDescriptor> settings;

        if (m_idToTrack.isValid()) {
            for (GameObject *object : QueryWorld::getAllGameObjects()) {
                if (object->getUniqueId() == m_idToTrack) {
                    Vector3D loc = object->getLocation();
                    ResourceDescriptor descriptor({
                                                          "View: " + getAssociatedView(),
                                                          "    Camera:",
                                                          "        Location: "
                                                          + std::to_string(loc.x()) + ","
                                                          + std::to_string(loc.y())
                                                  });
                    settings.push_back(descriptor);
                    break;
                }
            }
        }
        return settings;
    }

} // BattleRoom namespace
