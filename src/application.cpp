#include "battle_room/application.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/common/application_message_receiver.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/objects/object_factory.h"
#include "battle_room/user_interface/game_interface.h"
#include "battle_room/networking/world_updater_factory.h"

#include <thread>
#include <algorithm>

namespace BattleRoom {

    void sortByViewLayer(std::vector<ViewInterface *> &interfaces, ResourceDescriptor settings);

    Application::Application(ResourceDescriptor settings) {

        m_windows.clear();
        m_viewInterfaces.clear();

        applySettings(settings);
    }

    void Application::runApplicationLoop() {

        while (!InputGatherer::containsQuitEvent()) {

            // get inputs from last frame
            for (UniqueDisplayWindow &window : m_windows) {
                window->gatherInputs();
            }
            Inputs inputs = InputGatherer::getAndClearInputs();


            ///// start game interface thread
            std::thread interfaceThread([this, &inputs]() {

                    // Handle inputs view interfaces
                    for (ViewInterface *interface : m_viewInterfaces) {
                    inputs = interface->handleInputs(inputs);
                    }

                    // Update world for client
                    QueryWorld::updateBuffer();

                    // get any settings that need to be applied to windows
                    ResourceDescriptor settings;
                    for (ViewInterface *interface : m_viewInterfaces) {
                    settings.addSubResources(interface->getNewSettings());
                    }
                    for (UniqueDisplayWindow &window : m_windows) {
                    window->applySettings(settings);
                    }

                    // Prepare objects for display
                    for (ViewInterface *interface : m_viewInterfaces) {

                        std::string associatedView = interface->getAssociatedView();
                        std::vector<DrawableObject> objects = interface->getDrawableObjects();
                        std::vector<DrawableText> texts = interface->getDrawableTexts();
                        // TODO std::vector<DrawableMenu> menus = interface->getDrawableMenus();

                        for (UniqueDisplayWindow &window : m_windows) {
                            window->addViewObjects(objects, associatedView);
                            window->addViewTexts(texts, associatedView);
                            // TODO window->addViewMenus(menus, associatedView);
                        }
                    }

                    // Handle inputs for windows
                    for (UniqueDisplayWindow &window : m_windows) {
                        inputs = window->handleInputs(inputs);
                    }

                    // prevents the CPU from railing
                    std::this_thread::sleep_for(std::chrono::milliseconds(25));

            });
            ////// End game interface thread


            ///// Start Drawing "thread" - must be on main thread
            for (UniqueDisplayWindow &window : m_windows) {
                window->drawScreen();
            }
            //// End drawing "thread"

            interfaceThread.join();

            // Switch buffers that view objects and texts are written to
            for (UniqueDisplayWindow &window : m_windows) {
                window->switchBuffers();
            }

            // apply application message
            std::vector<ApplicationMessage> messages = ApplicationMessageReceiver::getAndClearMessages();
            for (auto& message : messages) {
                applyMessage(message);
            }
        }
    }

    void Application::applySettings(ResourceDescriptor settings) {

        ObjectFactory::applySettings(settings.getSubResource("ObjectTemplates"));

        // Create the world updater - empty if startup menu, or a server connection,
        // or a local updater
        m_worldUpdater = WorldUpdaterFactory::createWorldUpdater(settings.getSubResource("WorldUpdater"));


        // Create the windows for displaying - including view/camera setup in each
        for (ResourceDescriptor windowDescriptor : settings.getSubResources("Window")) {
            m_windows.push_back(createDisplayWindow(windowDescriptor));
        }


        // Create the game-to-view interfaces (each one points to a view)
        // These produce UI objects that are only seen locally and also
        // handle user inputs - for example, the main view of the world or the minimap
        for (ResourceDescriptor sub : settings.getSubResources("GameInterface")) {
            m_viewInterfaces.push_back(new GameInterface(sub));
        }


        // Collect the menus. These produce UI objects that are only seen locally and
        // also handle user inputs - they are menus...
        // TODO add menus to vew interfaces
        // TODO add an interface factory
        
        sortByViewLayer(m_viewInterfaces, settings);
    }

    void Application::addResource(ResourceDescriptor settings) {
        
        if (keyMatch("Window", settings.getKey())) {
            m_windows.push_back(createDisplayWindow(settings));
        } else if (keyMatch("GameInterface", settings.getKey())) {
            m_viewInterfaces.push_back(new GameInterface(settings));
        }
    }

    template <typename T> T findIn(std::vector<T>& vec, UniqueId target) {
        
        auto res = std::find_if(vec.begin(), vec.end(), 
             [target](const T v) -> bool { return v->getUniqueId() == target; });

        return res != vec.end() ? *res : nullptr;
    }

    template <typename R> R* findUniqueIn(std::vector<std::unique_ptr<R>>& vec, UniqueId target) {
        for (const auto& v : vec) {
            if (v->getUniqueId() == target) {
                return v.get();
            }
        }
        return nullptr;
    }

    void Application::modifyResource(UniqueId target, ResourceDescriptor settings) {

        Resource* resource = findIn(m_viewInterfaces, target);

        if (!resource) {
            resource = findUniqueIn(m_windows, target);
        }

        if (!resource && m_worldUpdater && m_worldUpdater->getUniqueId() == target) {
            resource = m_worldUpdater.get();
        }

        // apply
        if (resource) {
            resource->applySettings(settings);
        }
    }

    void Application::removeResource(UniqueId target) {

        auto res = std::find_if(m_viewInterfaces.begin(), m_viewInterfaces.end(), 
             [target](const ViewInterface* v) -> bool { return v->getUniqueId() == target; });
        if (res != m_viewInterfaces.end()) {
            delete *res;
            m_viewInterfaces.erase(res);
        }

        auto win = std::find_if(m_windows.begin(), m_windows.end(), 
             [target](const UniqueDisplayWindow& v) -> bool { return v->getUniqueId() == target; });
        if (win != m_windows.end()) {
            m_windows.erase(win);
        }

        if (m_worldUpdater && m_worldUpdater->getUniqueId() == target) {
            m_worldUpdater = nullptr;
        }
    }

    void Application::applyMessage(ApplicationMessage message) {

        if (ApplicationMessage::Type::Add == message.getType()) {
            addResource(message.getSettings());

        } else if (ApplicationMessage::Type::Modify == message.getType()) {
            modifyResource(message.getTarget(), message.getSettings());

        } else if (ApplicationMessage::Type::Remove == message.getType()) {
            removeResource(message.getTarget());

        }
    }

    void sortByViewLayer(std::vector<ViewInterface *> &interfaces, ResourceDescriptor settings) {

        // create a map of view names to view layers
        std::unordered_map<std::string, int> viewLayerMap;
        for (ResourceDescriptor window : settings.getSubResources("Window")) {
            for (ResourceDescriptor view : window.getSubResources("View")) {
                int viewLayer = 0;
                if (isNotEmpty(view.getSubResource("Layer").getValue())) {
                    viewLayer = std::stoi(view.getSubResource("Layer").getValue());
                }

                viewLayerMap.insert(std::make_pair(view.getValue(), viewLayer));
            }
        }

        // sort by created map
        std::sort(interfaces.begin(), interfaces.end(),
                [&viewLayerMap](ViewInterface *a, ViewInterface *b) {

                int aLayer = 0, bLayer = 0;
                if (viewLayerMap.count(a->getAssociatedView()) > 0) {
                aLayer = viewLayerMap.at(a->getAssociatedView());
                }
                if (viewLayerMap.count(b->getAssociatedView()) > 0) {
                bLayer = viewLayerMap.at(b->getAssociatedView());
                }
                return aLayer < bLayer;
                }
                );
    }

} // BattleRoom namespace
