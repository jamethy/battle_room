
#include "sdl_display_window.h"
#include "sdl_font_manager.h"
#include "sdl_helper_functions.h"

#include "resource_descriptor.h"
#include "input_gatherer.h"
#include "application_message_receiver.h"
#include "animation_handler.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "Logger.h"

#include <cmath>
#include <string>
#include <unordered_map>
#include <exception>
#include <iostream>
#include <algorithm>
#include <utility>

using std::string;
using std::vector;

namespace BattleRoom {

    unsigned SdlDisplayWindow::m_windowWithFocus = 1;

// apply settings

    void SdlDisplayWindow::applySettings(ResourceDescriptor settings) {

        SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);

        // if window name matches, settings are for this window
        if (m_windowName.compare(settings.getValue()) == 0) {

            // TODO figure out what a SDL_DisplayMode is

            ResourceDescriptor sub = settings.getSubResource("Width");
            if (isNotEmpty(sub.getValue())) {
                m_windowWidth = stoi(sub.getValue());
            }

            sub = settings.getSubResource("Height");
            if (isNotEmpty(sub.getValue())) {
                m_windowHeight = stoi(sub.getValue());
            }
        }
    }

    int SdlDisplayWindow::m_windowCount = 0;
    int SdlDisplayWindow::m_windowsDrawn = 0;
    vector<SDL_Event> SdlDisplayWindow::m_sdlEvents;

// constructors

    SdlDisplayWindow::SdlDisplayWindow(ResourceDescriptor settings) : 
        m_uniqueId(UniqueId::generateNewLocalId())
    {
        m_sdlEvents.clear();
        m_drawablesA.clear();
        m_drawablesB.clear();

        if (isNotEmpty(settings.getValue())) {
            m_windowName = settings.getValue();
        } else {
            m_windowName = "PROVIDE WINDOW DURING CONSTRUCTION.\n";
            Log::error("Must give a name during window construction.");
        }

        // TODO throw exceptions instead of cerr
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        }

        if (TTF_Init() != 0) {
            std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }

        m_window = SDL_CreateWindow(m_windowName.c_str(), 0, 0, 500, 500,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }

        ++m_windowCount;

        m_sdlTextureManager.setRenderer(m_renderer);

        applySettings(settings);
    }

    SdlDisplayWindow::~SdlDisplayWindow() {

        m_sdlTextureManager.clear();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);

        if (--m_windowCount <= 0) {
            SDL_Quit();
        }
    }


// other functions

    RelPixel calRel(Pixel p, Pixel topLeft, Pixel botRight) {
        return RelPixel(
                (p.getRow() - topLeft.getRow()) / (botRight.getRow() - topLeft.getRow()),
                (p.getCol() - topLeft.getCol()) / (botRight.getCol() - topLeft.getCol())
                );
    }

    void SdlDisplayWindow::gatherInputs(const std::vector<UniqueInterface>& views) {

        // For each SDL_Event that pertains to this window, create an Input
        for (vector<SDL_Event>::iterator it = m_sdlEvents.begin(); it != m_sdlEvents.end(); ++it) {

            SDL_Event event = *it;

            // Find special processes - anything non-window specific
            // If Ctrl-C is used, or the window is closed
            if (event.type == SDL_QUIT) {
                ApplicationMessageReceiver::addQuitEvent();
                continue;

                // if the OS is repeating a held down key, ignore it
            } else if (event.type == SDL_KEYDOWN && event.key.repeat != 0) {
                // Remove the SDL_Event from the events vector because
                // it has been dealt with (and adjust iterator)
                m_sdlEvents.erase(it);
                --it;
                continue;
            }

            unsigned windowId = SDL_GetWindowID(m_window);
            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_ENTER:
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        m_windowWithFocus = event.window.windowID;
                        if (windowId != m_windowWithFocus) {
                            m_mousePos = Pixel(-1, -1);
                        }
                }
            }

            // check if this is the right window
            if (m_windowWithFocus != windowId || getWindowIdFrom(event) != windowId) {
                continue;
            }

            Input input;

            // Set motion, key, and scroll amount
            switch (event.type) {
                case SDL_KEYDOWN:
                    input.setMotion(InputKey::Motion::PressedDown);
                    input.setKey(sdlKeyToInputKey(event.key.keysym.sym));
                    input.setModifiers(sdlModifierToInputModifier(event));
                    break;
                case SDL_KEYUP:
                    input.setMotion(InputKey::Motion::Released);
                    input.setKey(sdlKeyToInputKey(event.key.keysym.sym));
                    input.setModifiers(sdlModifierToInputModifier(event));
                    break;
                case SDL_MOUSEMOTION:
                    m_mousePos = Pixel(event.motion.y, event.motion.x);
                    input.setMotion(InputKey::Motion::None);
                    input.setKey(InputKey::Key::MouseOnly);
                    input.setModifiers(sdlModifierToInputModifier(event));
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    m_mousePos = Pixel(event.motion.y, event.motion.x);
                    input.setMotion(InputKey::Motion::PressedDown);
                    input.setKey(sdlMouseButtonToInputKey(event.button.button, event.button.clicks % 2));
                    input.setModifiers(sdlModifierToInputModifier(event));
                    break;
                case SDL_MOUSEBUTTONUP:
                    m_mousePos = Pixel(event.motion.y, event.motion.x);
                    input.setMotion(InputKey::Motion::Released);
                    input.setKey(sdlMouseButtonToInputKey(event.button.button, event.button.clicks));
                    input.setModifiers(sdlModifierToInputModifier(event));
                    break;
                case SDL_MOUSEWHEEL:
                    if (event.wheel.y != 0) { // maybe later use horizontal scrolling
                        input.setMotion(InputKey::Motion::Scroll);
                        input.setKey(InputKey::Key::MouseOnly);
                        input.setScrollAmount(event.wheel.y);
                        input.setModifiers(sdlModifierToInputModifier(event));
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        resizeViews(m_windowWidth, m_windowHeight, views);
                    }
                    break;
            }

            // Set view intersections
            for (auto& view : views) {

                // If it intersects the view, calculate the zero-plane intersection
                if (m_mousePos.isBetween(view->getTopLeft(), view->getBottomRight())) {

                    // Calculate the intersection point
                    Vector3D zeroPoint = view->zeroPlaneIntersection(m_mousePos);

                    // Add intersection to input's view list
                    input.addViewIntersection(view->getUniqueId(), zeroPoint);
                    px width = view->getBottomRight().getCol() - view->getTopLeft().getCol();
                    px height = view->getBottomRight().getRow() - view->getTopLeft().getRow();

                    relpx col = (m_mousePos.getCol() - view->getTopLeft().getCol())/width;
                    relpx row = (m_mousePos.getRow() - view->getTopLeft().getRow())/height;
                    input.addViewIntersection(view->getUniqueId(), RelPixel(row, col));
                }
            }

            // Add input to the input gatherer
            // Attain later with InputGatherer::getAndClearInputs
            InputGatherer::addInput(input);

            // Remove the SDL_Event from the events vector because
            // it has been dealt with (and adjust iterator)
            m_sdlEvents.erase(it);
            --it;
        }
    }

    const UniqueId SdlDisplayWindow::getUniqueId() const {
        return m_uniqueId;
    }

    std::string SdlDisplayWindow::getName() const {
        return m_windowName;
    }

    void SdlDisplayWindow::addViewDrawables(ViewInterface* view) {

        vector<UniqueDrawable> &drawables = m_drawingA ? m_drawablesB : m_drawablesA;

        for (const DrawableObject &object : view->getDrawableObjects()) {
            drawables.push_back(getSdlDrawableFrom(object, view));
        }

        for (const DrawableText &text : view->getDrawableTexts()) {
            drawables.push_back(getSdlDrawableFrom(text, view));
        }
        for (const DrawableMenu &menu : view->getDrawableMenus()) {
            drawables.push_back(getSdlDrawableFrom(menu, view));
        }
    }


    void SdlDisplayWindow::drawScreen() {

        // TODO clean this up and put it in functions/classes
        // TODO add in error catching
        // TODO use opengl to render so I can have skewed rectangles

        // Clear the screen by drawing it all dark grey
        SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
        SDL_RenderClear(m_renderer);

        vector<UniqueDrawable> &drawables = m_drawingA ? m_drawablesA : m_drawablesB;

        // Sort the drawables on the screen by view layer and position
        // This will ensure the right things are drawn ontop of the right tings
        std::sort(drawables.begin(), drawables.end(),
                  [](UniqueDrawable &a, UniqueDrawable &b) {
                      if (a->getViewLayer() == b->getViewLayer()) {
                          return a->getZPosition() < b->getZPosition();
                      } else {
                          return a->getViewLayer() > b->getViewLayer();
                      }
                  }
        );


        // For every drawable that has been collected, get the texture and draw it on the screen
        // If a texture is missing, use the missing animation texture
        for (UniqueDrawable &drawable : drawables) {
            drawable->draw(m_sdlTextureManager);
        }


        // Present the renderer
        SDL_RenderPresent(m_renderer);

        // Clear all the drawables that have been drawn to prepare for next frame
        drawables.clear();

        // Gather inputs
        if (m_windowsDrawn >= m_windowCount) {
            m_windowsDrawn = 0;
            m_sdlEvents.clear();
        }
        ++m_windowsDrawn;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            m_sdlEvents.push_back(event);
        }

    }

    void SdlDisplayWindow::switchBuffers() {
        m_drawingA = !m_drawingA;
    }

    UniqueDisplayWindow createDisplayWindow(ResourceDescriptor settings) {

        try {
            return UniqueDisplayWindow(new SdlDisplayWindow(settings));
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
    }

    void SdlDisplayWindow::resizeViews(int oldWidth, int oldHeight, const std::vector<UniqueInterface>& views) {

        int width = 0, height = 0;
        SDL_GetWindowSize(m_window, &width, &height);

        if (width <= 0 || height <= 0 || oldWidth <= 0 || oldHeight <= 0) {
            return;
        }
        m_windowWidth = width;
        m_windowHeight = height;

        for (const auto& view : views) {
            view->adjustForResize(width, height, oldWidth, oldHeight);
        }
    }

    int SdlDisplayWindow::getWidth() const {
        return m_windowWidth;
    }

    int SdlDisplayWindow::getHeight() const {
        return m_windowHeight;
    }

    TextureManager *SdlDisplayWindow::getTextureManager() {
        return &m_sdlTextureManager;
    }
} // BattleRoom namespace
