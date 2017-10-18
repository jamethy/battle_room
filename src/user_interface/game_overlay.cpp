#include "battle_room/user_interface/game_overlay.h"

using std::vector;

namespace BattleRoom {

// apply settings

    void GameOverlay::applySettings(ResourceDescriptor settings) {

        ViewInterface::applySettings(settings);

    }

// constructors

    GameOverlay::GameOverlay(ResourceDescriptor settings) {
            applySettings(settings);
    }

    vector<DrawableObject> GameOverlay::getDrawableObjects() {
        return vector<DrawableObject>();
    }

    vector<DrawableText> GameOverlay::getDrawableTexts() {
        return vector<DrawableText>();
    }

    Inputs GameOverlay::handleInputs(Inputs inputs) {
        return inputs;
    }

    vector<ResourceDescriptor> GameOverlay::getNewSettings() {
        return vector<ResourceDescriptor>();
    }

} // BattleRoom namespace

