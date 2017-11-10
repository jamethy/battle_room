#include "battle_room/user_interface/game_interface.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

#include "battle_room/common/animation_handler.h"

// probably will move
#include "battle_room/game/objects/player.h"

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

    GameInterface::GameInterface(ResourceDescriptor settings, UniqueId viewId) : 
        ViewInterface(viewId),
        m_idToTrack(UniqueId::generateInvalidId()),
        m_playerId(UniqueId::generateInvalidId())
    {
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

        if (m_selectedBackground.get()) {
            objects.push_back(DrawableObject(*m_selectedBackground));
        }
        if (m_chargingGun.get()) {
            objects.push_back(DrawableObject(*m_chargingGun));
        }
        if (m_chargingJump.get()) {
            objects.push_back(DrawableObject(*m_chargingJump));
        }

        return objects;
    }

    vector<DrawableText> GameInterface::getDrawableTexts() {
        return vector<DrawableText>();
    }

    vector<DrawableMenu> GameInterface::getDrawableMenus() {
        return vector<DrawableMenu>();
    }

    void GameInterface::updateAnimations(seconds timestep) {
        if (m_playerId.isValid()) {
            Player* player = (Player*)QueryWorld::getGameObject(m_playerId);
            if (player) {
                Vector3D loc = player->getLocation();
                if (m_selectedBackground) {
                    m_selectedBackground->setLocation(Vector3D(loc.x(), loc.y(), -0.1));
                }

                if (player->isChargingGun() && !m_chargingGun) {
                    m_chargingGun = UniqueDrawableObject(new DrawableObject());
                    m_chargingGun->setAnimation(AnimationHandler::getAnimation("spatial/charging_gun"));
                }

                if (m_chargingGun) {
                    if (player->isChargingGun()) {
                        m_chargingGun->setLocation(Vector3D(loc.x(), loc.y() - 1.25), 0.1));
                        if (player->getGunCharge() > 0.999) {

                            Animation &animation = m_chargingGun->getAnimation();
                            seconds newState = m_chargingGun->getAnimationState() + timestep;

                            if (newState > animation.getLength()) {

                                // find the new animation
                                m_chargingGun->setAnimation(AnimationHandler::getAnimation(animation.getNextAnimation()));

                                // set the new state (time elapsed since end of last animation)
                                m_chargingGun->setAnimationState(newState - animation.getLength());
                            } else {

                                // iterate object->animation
                                m_chargingGun->setAnimationState(newState);
                            }
                        } else {
                            m_chargingGun->setAnimationState(player->getGunCharge());
                        }
                    } else {
                        m_chargingGun = nullptr;
                    }
                }

                if (m_chargingJump) {
                }
            }
        }
    }

    Inputs GameInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;
        vector<Command> commands;

        for (Input input : inputs) {

            Command cmd;
            if (input.containsView(getAssociatedView())) {

                Vector3D viewInt = input.getViewIntersection(getAssociatedView());
                Vector2D point = Vector2D(viewInt.x(), viewInt.y());

                if (m_playerId.isValid()) {

                    if (Key::MouseOnly == input.getKey() 
                            && Motion::None == input.getMotion() 
                            && Modifier::Plain == input.getModifier()) {
                        cmd = Command(CommandType::Aim, m_playerId, point);

                    } else if (input.isKeyDown(Key::RightClick)) {
                        cmd = Command(CommandType::ShootCharge, m_playerId, point);

                    } else if (input.isKeyUp(Key::RightClick)) {
                        cmd = Command(CommandType::ShootRelease, m_playerId, point);

                    } else if (input.isKeyDown(Key::Space)) {
                        cmd = Command(CommandType::JumpCharge, m_playerId, point);

                    } else if (input.isKeyUp(Key::Space)) {
                        cmd = Command(CommandType::JumpRelease, m_playerId, point);

                    } else if (input.isKeyDown(Key::K)) {
                        cmd = Command(CommandType::Freeze, m_playerId, point);
                    } else if (input.isModKeyDown(Modifier::Shift, Key::K)) {
                        cmd = Command(CommandType::Unfreeze, m_playerId, point);
                    }
                }

                if (input.isKeyDown(Key::LeftClick)) {

                    // check spatial components
                    // check game objects
                    GameObject* obj = QueryWorld::findIntersectingObject(point);
                    if (obj != nullptr && ObjectType::Player == obj->getType()) {
                        m_playerId = obj->getUniqueId();
                        m_selectedBackground = UniqueDrawableObject(new DrawableObject());
                        m_selectedBackground->setAnimation(AnimationHandler::getAnimation("spatial/selected"));
                        m_chargingGun = nullptr;
                        m_chargingJump = nullptr;
                    } else {
                        m_playerId = UniqueId::generateInvalidId();
                        m_selectedBackground = nullptr;
                        m_chargingGun = nullptr;
                        m_chargingJump = nullptr;
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
                            "View: " + getAssociatedView().toString(),
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
