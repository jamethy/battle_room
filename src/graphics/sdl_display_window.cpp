
#include "sdl_display_window.h"
#include "sdl_font_manager.h"
#include "sdl_helper_functions.h"

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/input_gatherer.h"
#include "battle_room/common/animation_handler.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <cmath>
#include <string>
#include <unordered_map>
#include <exception>
#include <iostream>
#include <algorithm>

using std::string;
using std::vector;

namespace BattleRoom {

// apply settings

void SdlDisplayWindow::applySettings(ResourceDescriptor settings) {

    if (isNotEmpty(settings.getValue())) {
        SDL_SetWindowTitle(m_window, settings.getValue().c_str());
    }

    // TODO figure out what a SDL_DisplayMode is
    int width = 0, height = 0;
    SDL_GetWindowSize(m_window, &width, &height);
    if (width > 0 && height > 0) {

        ResourceDescriptor sub = settings.getSubResource("Width");
        if (isNotEmpty(sub.getValue())) {
            width = stoi(sub.getValue());
        }

        sub = settings.getSubResource("Height");
        if (isNotEmpty(sub.getValue())) {
            height = stoi(sub.getValue());
        }

        SDL_SetWindowSize(m_window, width, height);
    }

    for (ResourceDescriptor sub : settings.getSubResources("View")) {

        // If view exists, apply settings
        if (m_views.count(sub.getValue()) > 0) {
            View& view = m_views.at(sub.getValue());
            view.applySettings(sub);
        }
        // Else, create a new view
        else {
            View newView = View(sub);
            // Check if bottom right was set, if not use window dimensions
            Pixel botRight = newView.getBottomRight();
            if(botRight.getColInt() == 0 && botRight.getRowInt() == 0) {
                newView.setBottomRight(Pixel(height,width));
            }
            // Add it to the view
            addView(newView);
        }
    }
}

int SdlDisplayWindow::m_windowCount = 0;
int SdlDisplayWindow::m_windowsDrawn = 0;
vector<SDL_Event> SdlDisplayWindow::m_sdlEvents;

// constructors

SdlDisplayWindow::SdlDisplayWindow(ResourceDescriptor settings)
{
    m_views.clear();
    m_sdlEvents.clear();
    m_drawablesA.clear();
    m_drawablesB.clear();

    // TODO throw exceptions instead of cerr
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
    }

    if (TTF_Init() != 0){
        std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    m_window = SDL_CreateWindow("new_window", 0, 0, 500, 500, SDL_WINDOW_SHOWN);
    if (m_window == nullptr){
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr){
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


// utilitiy funcitons

/**
 * \brief Sorts views by layer (ascending)
 * As a reminder, higher layers are rendered first and then covered by lower layers
 * \param viewMap Map of views to sort
 * \return Names of sorted values
 */
vector<string> getSortedViews(const std::unordered_map<string,View>& viewMap) {

    vector<string> sortedViews(viewMap.size());
    sortedViews.clear();
    for (const std::pair<string,View>& p : viewMap) {
        sortedViews.push_back(p.first);
    }

    std::sort(sortedViews.begin(), sortedViews.end(), 
            [&viewMap](string a, string b) {
                return viewMap.at(a).getLayer() < viewMap.at(b).getLayer();
            }
    );
    return sortedViews;
}

// other functions

void SdlDisplayWindow::gatherInputs() {

    // Track the mouse position by updating when available
    static Pixel mousePos(0,0);

    // For each SDL_Event that pertains to this window, create an Input
    for (vector<SDL_Event>::iterator it = m_sdlEvents.begin(); it != m_sdlEvents.end(); ++it) {

        SDL_Event event = *it;

        // Find special processes - anything non-window specific
        // If Ctrl-C is used, or the window is closed
        if (event.type == SDL_QUIT) {
            InputGatherer::addQuitEvent();
            continue;

        // if the OS is repeating a held down key, ignore it
        } else if (event.type == SDL_KEYDOWN && event.key.repeat != 0) {
            // Remove the SDL_Event from the events vector because
            // it has been dealt with (and adjust iterator)
            m_sdlEvents.erase(it); --it;
            continue;
        }


        // check if this is the right window
        if (getWindowIdFrom(event) != SDL_GetWindowID(m_window)) {
            continue;
        }


        Input input;

        // Set motion, key, and scroll amount
        switch (event.type) {
            case SDL_KEYDOWN:
                input.setMotion(InputKey::Motion::PressedDown);
                input.setKey(sdlKeyToInputKey(event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                input.setMotion(InputKey::Motion::Released);
                input.setKey(sdlKeyToInputKey(event.key.keysym.sym));
                break;
            case SDL_MOUSEMOTION:
                mousePos = Pixel(event.motion.y, event.motion.x);
                input.setMotion(InputKey::Motion::None);
                input.setKey(InputKey::Key::MouseOnly);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mousePos = Pixel(event.motion.y, event.motion.x);
                input.setMotion(InputKey::Motion::PressedDown);
                input.setKey(sdlMouseButtonToInputKey(event.button.button, event.button.clicks));
                break;
            case SDL_MOUSEBUTTONUP:
                mousePos = Pixel(event.motion.y, event.motion.x);
                input.setMotion(InputKey::Motion::Released);
                input.setKey(sdlMouseButtonToInputKey(event.button.button, event.button.clicks));
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y != 0) { // maybe later use horizontal scrolling
                    input.setMotion(InputKey::Motion::Scroll);
                    input.setKey(InputKey::Key::MouseOnly);
                    input.setScrollAmount(event.wheel.y); 
                }
                break;
        }

        // Set view intersections
        for (string& viewName : getSortedViews(m_views)) {
            const View& view = m_views.at(viewName);

            // If it intersects the view, calculate the zero-plane intersection
            if (mousePos.isBetween(view.getTopLeft(), view.getBottomRight())) {

                // Calculate the intersection point
                Vector3D zeroPoint = view.zeroPlaneIntersection(mousePos);

                // Add intersection to input's view list
                input.addViewIntersection(view.getName(), zeroPoint);
            }
        }

        // Add input to the input gatherer 
        // Attain later with InputGatherer::getAndClearInputs
        InputGatherer::addInput(input);

        // Remove the SDL_Event from the events vector because
        // it has been dealt with (and adjust iterator)
        m_sdlEvents.erase(it); --it;
    }

    // This is not good practice but doing it anyway...
    m_drawingA = !m_drawingA;
}

Inputs SdlDisplayWindow::handleInputs(Inputs inputs) {

    // Send inputs to each view to handle
    for (string& viewName : getSortedViews(m_views)) {
        View& view = m_views.at(viewName);
        inputs = view.handleInputs(inputs);
    }

    return inputs;
}

void SdlDisplayWindow::addViewObjects(vector<DrawableObject> objects, string viewName) {

    // Check if view is in this window
    if (m_views.count(viewName) > 0) {

        View& view = m_views.at(viewName);
        vector<UniqueDrawable>& drawables = m_drawingA ? m_drawablesB : m_drawablesA;

        for (DrawableObject& object : objects) {
            drawables.push_back(getSdlDrawableFrom(object,view));
        }
    }
}

void SdlDisplayWindow::addViewTexts(std::vector<DrawableText> texts, std::string viewName) {

    if (m_views.count(viewName) > 0) {

        View& view = m_views.at(viewName);
        vector<UniqueDrawable>& drawables = m_drawingA ? m_drawablesB : m_drawablesA;

        for (DrawableText& text : texts) {
            drawables.push_back(getSdlDrawableFrom(text,view));
        }
    }
}



void SdlDisplayWindow::drawScreen() {

    // TODO clean this up and put it in functions/classes
    // TODO add in error catching
    // TODO use opengl to render so I can have skewed rectangles

    // Clear the screen by drawing it all black
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    vector<UniqueDrawable>& drawables = m_drawingA ? m_drawablesA : m_drawablesB;

    // Sort the drawables on the screen by view layer and position
    // This will ensure the right things are drawn ontop of the right tings
    std::sort(drawables.begin(), drawables.end(), 
            [](UniqueDrawable& a, UniqueDrawable& b) {
                if (a->getViewLayer() == b->getViewLayer()) { 
                    return a->getZPosition() < b->getZPosition();
                }
                else { 
                    return a->getViewLayer() < b->getViewLayer();
                }
            }
    );
    

    // For every drawable that has been collected, get the texture and draw it on the screen
    // If a texture is missing, use the missing animation texture
    for (UniqueDrawable& drawable : drawables) {
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

void SdlDisplayWindow::addView(View view) {

    string name = view.getName();

    if (m_views.count(name) > 0) {
        m_views.at(name) = view;
    }
    else {
        m_views.insert(std::pair<string,View>(name,view));
    }
}

UniqueDisplayWindow createDisplayWindow(ResourceDescriptor settings) {

    try
    {
        return UniqueDisplayWindow(new SdlDisplayWindow(settings));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

} // BattleRoom namespace
