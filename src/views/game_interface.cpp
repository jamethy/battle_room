#include "views/game_interface.h"
#include "application/input_gatherer.h"
#include "world/query_world.h"
#include "world/command_receiver.h"
#include "animation/animation_handler.h"
#include "include/cef_parser.h"

// probably will move
#include "world/player.h"
#include "common/logger.h"

using std::vector;
using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

namespace BattleRoom {

// apply settings

    void GameInterface::applySettings(ResourceDescriptor settings) {
        View::applySettings(settings);

        ResourceDescriptor sub = settings.getSubResource("Url");
        if (isNotEmpty(sub.getValue())) {
            url = sub.getValue();
            m_htmlMenu->navigateTo(url);
        }
    }

    ResourceDescriptor GameInterface::getSettings() const {
        auto rd = View::getSettings();
        rd.emplaceSubResource("Type", "Game");
        rd.emplaceSubResource("Url", url);
        return rd;
    }

// constructors

    GameInterface::GameInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth,
                                 int windowHeight) :
            View(settings, windowWidth, windowHeight),
            m_idToTrack(UniqueId::generateInvalidId()),
            m_playerId(UniqueId::generateInvalidId()),
            m_htmlMenu(new HtmlMenu(textureManager, windowWidth, windowHeight, this)) {
        applySettings(settings);
    }

// other functions

    WebMessageResponse GameInterface::onMessage(const std::string &message) {

        CefRefPtr<CefDictionaryValue> requestValue = CefParseJSON(CefString(message), JSON_PARSER_RFC)->GetDictionary();
        auto method = requestValue->GetString("method").ToString();
        auto route = requestValue->GetString("route").ToString();

        int responseCode = WebMessageResponse::SUCCESS_CODE;
        std::string response;

        if (method == "GET" && route == "/game-elements") {
            if (m_playerSelect) {
                response = "[" + m_playerSelect->getJson(m_camera.get(), this) + "]";
            } else {
                response = "[]";
            }
        } else {
            responseCode = WebMessageResponse::NOT_FOUND_CODE;
        }

        return {responseCode, response};
    }

    vector<DrawableObject> GameInterface::getDrawableObjects() {

        vector<DrawableObject> objects = {};

        for (const auto &obj : QueryWorld::getBackgroundObjects()) {
            objects.emplace_back(*obj);
        }

        for (const auto &obj : QueryWorld::getAllGameObjects()) {
            objects.emplace_back(*obj);
        }

        if (m_selectedBackground.get()) {
            objects.emplace_back(*m_selectedBackground);
        }

        return objects;
    }

    vector<DrawableMenu> GameInterface::getDrawableMenus() {
        return {m_htmlMenu->getDrawableMenu()};
    }

    void moveCameraToCenter(Camera *camera, UniqueId uniqueId) {

        if (uniqueId.isValid()) {
            const GameObject *obj = QueryWorld::getGameObject(uniqueId);
            if (obj) {
                Vector3D loc = obj->getLocation();
                camera->setLocation(Vector3D(loc.x(), loc.y(), camera->getLocation().z()));
            }
        }
    }

    void GameInterface::update(seconds timestep) {
        (void) timestep; // unused

        if (m_playerId.isValid()) {
            const auto *player = (const Player *) QueryWorld::getGameObject(m_playerId);
            if (player) {
                Vector3D loc = player->getLocation();
                if (m_selectedBackground) {
                    m_selectedBackground->setLocation(Vector3D(loc.x(), loc.y(), -0.1));
                }

                if (!m_playerSelect) {
                    m_playerSelect = std::unique_ptr<PlayerSelect>(new PlayerSelect());
                }
                m_playerSelect->update(player);
            } else if (m_playerSelect) {
                m_playerSelect = nullptr;
            }
        }

        moveCameraToCenter(m_camera.get(), m_idToTrack);
    }

    Inputs GameInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;
        vector<Command> commands;

        // TODO figure out better way
        UniqueId playerClientId = UniqueId::generateInvalidId();
        const auto *player = (const Player *) QueryWorld::getGameObject(m_playerId);
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
                        && input.getModifiers().isPlain()) {
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
                    const GameObject *clientPlayer = QueryWorld::getClientPlayer();
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
                        const GameObject *clientPlayer = QueryWorld::getClientPlayer();
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
                    const GameObject *obj = QueryWorld::findIntersectingObject(point);
                    if (obj != nullptr && ObjectType::Player == obj->getType()) {
                        m_playerId = obj->getUniqueId();
                        m_selectedBackground = UniqueDrawableObject(new DrawableObject());
                        m_selectedBackground->setAnimation(AnimationHandler::getAnimation("spatial/selected"));
                    } else {
                        m_playerId = UniqueId::generateInvalidId();
                        m_idToTrack = UniqueId::generateInvalidId();
                        m_selectedBackground = nullptr;
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

    void GameInterface::adjustForResize(int width, int height, int oldWidth, int oldHeight) {
        View::adjustForResize(width, height, oldWidth, oldHeight);
        m_htmlMenu->resize(width, height);
    }

} // BattleRoom namespace
