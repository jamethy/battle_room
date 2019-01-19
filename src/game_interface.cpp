#include "game_interface.h"

#include "input_gatherer.h"
#include "query_world.h"
#include "command_receiver.h"

#include "animation_handler.h"

// probably will move
#include "player.h"

using std::vector;
using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

namespace BattleRoom {

// apply settings

    void GameInterface::applySettings(ResourceDescriptor settings) {
        View::applySettings(settings);
    }

// constructors

    GameInterface::GameInterface(ResourceDescriptor settings, int windowWidth, int windowHeight) : 
        View(settings, windowWidth, windowHeight),
        m_idToTrack(UniqueId::generateInvalidId()),
        m_playerId(UniqueId::generateInvalidId())
    {
            applySettings(settings);
    }

// other functions

    vector<DrawableObject> GameInterface::getDrawableObjects() {

        vector<DrawableObject> objects;
        objects.clear();

        for (const auto& obj : QueryWorld::getBackgroundObjects()) {
            objects.emplace_back(*obj);
        }

        for (const auto& obj : QueryWorld::getAllGameObjects()) {
            objects.emplace_back(*obj);
        }

        if (m_selectedBackground.get()) {
            objects.emplace_back(*m_selectedBackground);
        }
        if (m_chargingGun.get()) {
            objects.emplace_back(*m_chargingGun);
        }
        if (m_chargingJump.get()) {
            objects.emplace_back(*m_chargingJump);
        }

        return objects;
    }

    vector<DrawableText> GameInterface::getDrawableTexts() {
        return vector<DrawableText>();
    }

    vector<DrawableMenu> GameInterface::getDrawableMenus() {
        return vector<DrawableMenu>();
    }

    void moveCameraToCenter(Camera* camera, UniqueId uniqueId) {

        if (uniqueId.isValid()) {
            const GameObject* obj = QueryWorld::getGameObject(uniqueId);
            if (obj) {
                Vector3D loc = obj->getLocation();
                camera->setLocation(Vector3D(loc.x(), loc.y(), camera->getLocation().z()));
            }
        }
    }

    void GameInterface::update(seconds timestep) {
        if (m_playerId.isValid()) {
            const auto * player = (const Player*)QueryWorld::getGameObject(m_playerId);
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

                        // orient gun charge bar
                        Vector3D diff(0, -1.25, 0);
                        diff = m_camera->getOrientation().getRotated(diff);
                        m_chargingGun->setLocation(Vector3D(loc.x(), loc.y(), 0.1).plus(diff));
                        m_chargingGun->setOrientation(m_camera->getOrientation());

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
                } else {
                    m_chargingGun = nullptr;
                }

                if (m_chargingJump) {
                }
            }
        }

        moveCameraToCenter(m_camera.get(), m_idToTrack);
    }

    Inputs GameInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;
        vector<Command> commands;

        // TODO figure out better way
        UniqueId playerClientId = UniqueId::generateInvalidId();
        const auto * player = (const Player*)QueryWorld::getGameObject(m_playerId);
        if (player) {
            playerClientId = player->getClient();
        }
        UniqueId client = QueryWorld::getClientId();

        for (Input input : inputs) {

            Command cmd;
            if (input.containsView(getUniqueId())) {

                Vector3D viewInt = input.getViewIntersection(getUniqueId());
                Vector2D point = Vector2D(viewInt.x(), viewInt.y());

                if (m_playerId.isValid() && playerClientId == client) {

                    if (Key::MouseOnly == input.getKey() 
                            && Motion::None == input.getMotion() 
                            && Modifier::Plain == input.getModifiers().isPlain()) {
                        cmd = Command(CommandType::Aim, m_playerId, client, point);

                    } else if (input.isKeyDown(Key::RightClick)) {
                        cmd = Command(CommandType::ShootCharge, m_playerId, client, point);

                    } else if (input.isKeyUp(Key::RightClick)) {
                        cmd = Command(CommandType::ShootRelease, m_playerId, client, point);

                    } else if (input.isKeyDown(Key::Space)) {
                        cmd = Command(CommandType::JumpCharge, m_playerId, client, point);

                    } else if (input.isKeyUp(Key::Space)) {
                        cmd = Command(CommandType::JumpRelease, m_playerId, client, point);

                    } else if (input.isKeyDown(Key::K)) {
                        cmd = Command(CommandType::Freeze, m_playerId, client, point);
                    } else if (input.isModKeyDown(Modifier::Shift, Key::K)) {
                        cmd = Command(CommandType::Unfreeze, m_playerId, client, point);
                    }
                }

                if (input.isKeyDown(Key::C)) {
                    const GameObject* clientPlayer = QueryWorld::getClientPlayer();
                    if (clientPlayer) {
                        m_playerId = clientPlayer->getUniqueId();
                        m_selectedBackground = UniqueDrawableObject(new DrawableObject());
                        m_selectedBackground->setAnimation(AnimationHandler::getAnimation("spatial/selected"));
                        moveCameraToCenter(m_camera.get(), m_playerId);
                    }

                } else if (input.isKeyDown(Key::T)) {
                    if (m_idToTrack.isValid()) {
                        m_idToTrack = UniqueId::generateInvalidId();
                    } else {
                        const GameObject* clientPlayer = QueryWorld::getClientPlayer();
                        if (clientPlayer) {
                            m_playerId = clientPlayer->getUniqueId();
                            m_selectedBackground = UniqueDrawableObject(new DrawableObject());
                            m_selectedBackground->setAnimation(AnimationHandler::getAnimation("spatial/selected"));
                            moveCameraToCenter(m_camera.get(), m_playerId);
                            m_idToTrack = m_playerId;
                        }
                    }

                } else if (input.isKeyDown(Key::LeftClick)) {

                    // check spatial components
                    // check game objects
                    const GameObject* obj = QueryWorld::findIntersectingObject(point);
                    if (obj != nullptr && ObjectType::Player == obj->getType()) {
                        m_playerId = obj->getUniqueId();
                        m_selectedBackground = UniqueDrawableObject(new DrawableObject());
                        m_selectedBackground->setAnimation(AnimationHandler::getAnimation("spatial/selected"));
                        m_chargingGun = nullptr;
                        m_chargingJump = nullptr;
                    } else {
                        m_playerId = UniqueId::generateInvalidId();
                        m_idToTrack = UniqueId::generateInvalidId();
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

        return View::handleInputs(remainingInputs);
    }

} // BattleRoom namespace
