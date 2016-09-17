#include "battle_room/user_interface/game_interface.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/networking/server_client_factory.h"

using std::vector;

namespace BattleRoom {

// apply settings

void GameInterface::applySettings(ResourceDescriptor settings) {

    ViewInterface::applySettings(settings);

    ResourceDescriptor sub = settings.getSubResource("ServerClient");
    if (isNotEmpty(sub.getValue())) {
        m_serverClient = ServerClientFactory::createServerClient(sub);
    }
}

// constructors

GameInterface::GameInterface(ResourceDescriptor settings) 
    : m_serverClient(ServerClientFactory::createEmptyServerClient())
{ 
    applySettings(settings);
}

GameInterface::GameInterface(const GameInterface& original) 
    : ViewInterface(original),
      m_serverClient(UniqueServerClient(original.m_serverClient->clone()))
{ 
}

GameInterface& GameInterface::operator=(const GameInterface& original) {
    m_serverClient = UniqueServerClient(original.m_serverClient->clone());
    return *this;
}

// other functions

void GameInterface::updateBuffer() {
    m_serverClient->updateBuffer();
}

vector<DrawableObject> GameInterface::getDrawableObjects() {

    vector<DrawableObject> objects;
    objects.clear();

    for (GameObject& obj : m_serverClient->getAllGameObjects()) {
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


    return remainingInputs;
}

} // BattleRoom namespace
