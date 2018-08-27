#include <utility>

#include "application.h"

#include "input_gatherer.h"
#include "application_message_receiver.h"
#include "query_world.h"
#include "object_factory.h"
#include "interface_factory.h"
#include "world_updater_factory.h"
#include "client_connection.h"
#include "server_connection.h"

#include <thread>
#include <algorithm>
#include <chrono>
#include <iostream>

using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

namespace BattleRoom {

    Application::Application(ResourceDescriptor settings) {

        m_windows.clear();
        m_viewMap.clear();

        applySettings(std::move(settings));
    }

    void Application::runApplicationLoop() {

        steady_clock::time_point lastTime = steady_clock::now();

        while (!ApplicationMessageReceiver::containsQuitEvent()) {

            // get loop delta
            steady_clock::time_point now = steady_clock::now();
            seconds timestep = duration_cast<duration<double>>(now - lastTime).count();
            lastTime = now;

            // get inputs from last frame
            for (const UniqueDisplayWindow &window : m_windows) {
                window->gatherInputs(m_viewMap.at(window->getUniqueId()));
            }
            Inputs inputs = InputGatherer::getAndClearInputs();

            ///// start game interface thread
            std::thread interfaceThread([this, &inputs, &timestep]() {

                    // Handle inputs view interfaces
                    for (const UniqueDisplayWindow &window : m_windows) {
                        for (const auto& interface : m_viewMap.at(window->getUniqueId())) {
                            inputs = interface->handleInputs(inputs);
                        }
                    }

                    // Update world for client
                    QueryWorld::updateBuffer();

                    // Prepare objects for display
                    for (const UniqueDisplayWindow &window : m_windows) {
                        for (const auto& interface : m_viewMap.at(window->getUniqueId())) {

                            interface->update(timestep);
                            window->addViewDrawables(interface.get());
                        }
                    }

                    m_worldUpdater->clientUpdate();

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
        for (ResourceDescriptor window : settings.getSubResources("Window")) {
            addResource(window);
        }

        for (ResourceDescriptor interface : settings.getSubResources("Interface")) {
            addResource(interface);
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

    DisplayWindow* findWindow(std::vector<UniqueDisplayWindow>& vec, std::string val) {

        if (isEmpty(val)) {
            return nullptr;
        }

        UniqueId id = UniqueId::fromString(val);

        if (id.isValid()) {
            for (const auto& w : vec) {
                if (w->getUniqueId() == id) {
                    return w.get();
                }
            }
        }

        for (const auto& w : vec) {
            if (keyMatch(w->getName(), val)) {
                return w.get();
            }
        }

        return nullptr;
    }

    void Application::addResource(ResourceDescriptor settings) {
        
        if (keyMatch("Window", settings.getKey())) {
            addWindow(settings);
        } else if (keyMatch("Interface", settings.getKey())) {

            ResourceDescriptor sub = settings.getSubResource("Window");
            DisplayWindow* window = findWindow(m_windows, sub.getValue());
            if (window) {
                addViewTo(window->getUniqueId(), settings);
            }
        } else if (keyMatch("WorldUpdater", settings.getKey())) {
            m_worldUpdater = WorldUpdaterFactory::createWorldUpdater(settings);
        } 
    }

    void Application::modifyResource(UniqueId target, ResourceDescriptor settings) {

        Resource* resource = findUniqueIn(m_windows, target);

        if (!resource) {
            for (const auto& window : m_windows) {
                resource = findUniqueIn(m_viewMap.at(window->getUniqueId()), target);
                if (resource) {
                    break;
                }
            }
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

        if (removeWindow(target)) {
            return;
        }

        if (removeView(target)) {
            return;
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
        } else if (ApplicationMessage::Type::Quit == message.getType()) {
            ApplicationMessageReceiver::addQuitEvent();
        }
    }

    std::vector<UniqueInterface>::iterator getViewPos(std::vector<UniqueInterface>& vec, int layer) {
        std::vector<UniqueInterface>::iterator itr;
        for (itr = vec.begin(); itr != vec.end(); ++itr) {
            if (layer <= (*itr)->getLayer()) {
                break;
            }
        }
        return itr;
    }

    void Application::addViewTo(UniqueId windowId, ResourceDescriptor settings) {
        if (windowId.isValid()) {
            DisplayWindow* window = findUniqueIn(m_windows, windowId);
            if (window) {

                auto interface = InterfaceFactory::createInterface(settings, 
                        window->getWidth(), window->getHeight());

                auto& vec = m_viewMap.at(windowId);
                auto itr = getViewPos(vec, interface->getLayer());
                vec.insert(itr, std::move(interface));
            }
        }
    }

    bool Application::removeView(UniqueId viewId) {

        for (auto& windowViews : m_viewMap) {
            auto& vec = windowViews.second;
            auto res = std::find_if(vec.begin(), vec.end(), 
                    [viewId](const UniqueInterface& v) -> bool { return v->getUniqueId() == viewId; });
            if (res != vec.end()) {
                vec.erase(res);
                return true;
            }
        }
        return false;
    }

    void Application::addWindow(ResourceDescriptor settings) {
        auto window = createDisplayWindow(settings);
        m_viewMap.emplace(window->getUniqueId(), std::vector<UniqueInterface>());
        m_windows.push_back(std::move(window));
    }

    bool Application::removeWindow(UniqueId windowId) {

        auto win = std::find_if(m_windows.begin(), m_windows.end(), 
             [windowId](const UniqueDisplayWindow& v) -> bool { return v->getUniqueId() == windowId; });
        if (win != m_windows.end()) {
            m_windows.erase(win);
            m_viewMap.erase(windowId);
            return true;
        }
        return false;
    }

} // BattleRoom namespace
