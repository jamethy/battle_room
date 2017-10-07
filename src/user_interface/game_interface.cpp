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
            : m_idToTrack(UniqueId::generateInvalidId()) {
        applySettings(settings);
    }

// other functions

    vector<DrawableObject> GameInterface::getDrawableObjects() {

        vector<DrawableObject> objects;
        objects.clear();

        for (DrawableObject *obj : QueryWorld::getBackgroundObjects()) {
            objects.push_back(DrawableObject(*obj));
        }

        for (GameObject *obj : QueryWorld::getAllGameObjects()) {
            objects.push_back(DrawableObject(*obj));
        }
        return objects;
    }

    vector<DrawableText> GameInterface::getDrawableTexts() {
        return vector<DrawableText>();
    }

    UniqueId getPlayerId() {
        for (GameObject *obj : QueryWorld::getAllGameObjects()) {
            if (obj->getName().compare("man") == 0) {
                return obj->getUniqueId();
            }
        }
        return UniqueId::generateInvalidId();
    }

    Inputs GameInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;
        vector<Command> commands;
        UniqueId player = getPlayerId();

        for (Input input : inputs) {

            // temp for easy testing and quitting
            if (input.getMotion() == InputKey::Motion::PressedDown) {
                if (input.getKey() == InputKey::Key::Q) {
                    InputGatherer::addQuitEvent();
                }
            }

            Command cmd;
            if (input.containsView(getAssociatedView())) {

                if (player.isValid()) {

                    Vector3D viewInt = input.getViewIntersection(getAssociatedView());
                    Vector2D point = Vector2D(viewInt.x(), viewInt.y());

                    if (InputKey::Key::MouseOnly == input.getKey() && InputKey::Motion::None == input.getMotion()) {
                        cmd = Command(CommandType::Aim, player, point);

                    } else if (input.isKeyDown(InputKey::Key::RightClick)) {
                        cmd = Command(CommandType::ShootCharge, player, point);

                    } else if (input.isKeyUp(InputKey::Key::RightClick)) {
                        cmd = Command(CommandType::ShootRelease, player, point);

                    } else if (input.isKeyDown(InputKey::Key::Space)) {
                        cmd = Command(CommandType::JumpCharge, player, point);

                    } else if (input.isKeyUp(InputKey::Key::Space)) {
                        cmd = Command(CommandType::JumpRelease, player, point);

                    } else if (input.isKeyDown(InputKey::Key::K)) {
                        cmd = Command(CommandType::Freeze, player, point);
                    }
                }
            }

            if (cmd.getType() == CommandType::Invalid) {
                remainingInputs.addInput(input);
            } else {
                commands.push_back(cmd);
            }
        }

        CommandReceiver::addCommands(commands);

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
