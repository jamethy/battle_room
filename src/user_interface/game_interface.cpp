#include "battle_room/user_interface/game_interface.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

using std::vector;
using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

namespace BattleRoom {

// apply settings

    void GameInterface::applySettings(ResourceDescriptor settings) {

        ViewInterface::applySettings(settings);

    }

// constructors

    GameInterface::GameInterface(ResourceDescriptor settings) : 
        m_idToTrack(UniqueId::generateInvalidId()),
        m_selectedObject(UniqueId::generateInvalidId()) {
            m_spatialElements.clear();
            applySettings(settings);
    }

// other functions

    vector<DrawableObject> GameInterface::getDrawableObjects() {

        vector<DrawableObject> objects;
        objects.clear();

        for (DrawableObject *obj : QueryWorld::getBackgroundObjects()) {
            objects.push_back(DrawableObject(*obj));
        }

        std::vector<GameObject*> gameObjects = QueryWorld::getAllGameObjects();
        for (GameObject *obj : gameObjects) {
            objects.push_back(DrawableObject(*obj));
        }

        for (SpatialElement* sptl : m_spatialElements) {
            sptl->update(gameObjects);
            objects.push_back(DrawableObject(*sptl));
        }

        return objects;
    }

    vector<DrawableText> GameInterface::getDrawableTexts() {
        return vector<DrawableText>();
    }

    bool objectBoundaryContains(GameObject* obj, Vector2D point) {

        Vector2D relP = point
            .minus(obj->getPosition())
            .getRotated(obj->getRotation());

        return obj->getAnimation()
            .getFrame(obj->getAnimationState())
            .getBoundarySet()
            .contains(relP);
    }

    GameObject* findIntersectingObject(std::vector<GameObject*>& objects, Vector2D point) {
        for (GameObject* obj : objects) {
            if (objectBoundaryContains(obj, point)) {
                return obj; 
            }
        }
        return nullptr;
    }

    GameObject* getPlayerId() {
        for (GameObject *obj : QueryWorld::getAllGameObjects()) {
            if (obj->getName().compare("man") == 0) {
                return obj;
            }
        }
        return nullptr;
    }

    Inputs GameInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;
        vector<Command> commands;

        std::vector<GameObject*> gameObjects = QueryWorld::getAllGameObjects();

        for (Input input : inputs) {

            // temp for easy testing and quitting
            if (input.getMotion() == Motion::PressedDown) {
                if (input.getKey() == Key::Q) {
                    InputGatherer::addQuitEvent();
                }
            }

            Command cmd;
            if (input.containsView(getAssociatedView())) {

                Vector3D viewInt = input.getViewIntersection(getAssociatedView());
                Vector2D point = Vector2D(viewInt.x(), viewInt.y());

                if (m_selectedObject.isValid()) {

                    if (Key::MouseOnly == input.getKey() && Motion::None == input.getMotion()) {
                        cmd = Command(CommandType::Aim, m_selectedObject, point);

                    } else if (input.isKeyDown(Key::RightClick)) {
                        cmd = Command(CommandType::ShootCharge, m_selectedObject, point);

                    } else if (input.isKeyUp(Key::RightClick)) {
                        cmd = Command(CommandType::ShootRelease, m_selectedObject, point);

                    } else if (input.isKeyDown(Key::Space)) {
                        cmd = Command(CommandType::JumpCharge, m_selectedObject, point);

                    } else if (input.isKeyUp(Key::Space)) {
                        cmd = Command(CommandType::JumpRelease, m_selectedObject, point);

                    } else if (input.isKeyDown(Key::K)) {
                        cmd = Command(CommandType::Freeze, m_selectedObject, point);
                    }
                }

                if (input.isKeyDown(Key::LeftClick)) {

                    // check spatial components
                    // check game objects
                    GameObject* obj = findIntersectingObject(gameObjects, point);
                    if (obj != nullptr) {
                        m_selectedObject = obj->getUniqueId();
                        m_spatialElements.push_back(new SpatialElement(m_selectedObject));
                    } else {
                        m_spatialElements.clear();
                        m_selectedObject = UniqueId::generateInvalidId();
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
