
#include "sdl_display_window.h"
#include "sdl_font_manager.h"
#include "sdl_helper_functions.h"

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/input_gatherer.h"
#include "battle_room/engine/animation/animation_handler.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <cmath>
#include <limits>
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

    string newName = settings.getValue();
    if (!newName.empty()) {
        SDL_SetWindowTitle(m_window, newName.c_str());
    }

    // TODO figure out what a SDL_DisplayMode is
    int width = 0, height = 0;
    SDL_GetWindowSize(m_window, &width, &height);
    if (width > 0 && height > 0) {

        ResourceDescriptor sub = settings.getSubResource("Width");
        if (!sub.getKey().empty()) {
            width = stoi(sub.getValue());
        }

        sub = settings.getSubResource("Height");
        if (!sub.getKey().empty()) {
            height = stoi(sub.getValue());
        }

        SDL_SetWindowSize(m_window, width, height);
    }

    for (ResourceDescriptor sub : settings.getSubResources("View")) {
        addView(View(sub));
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

    static Pixel mousePos(0,0);

    for (vector<SDL_Event>::iterator it = m_sdlEvents.begin(); it != m_sdlEvents.end(); ++it) {

        SDL_Event event = *it;

        // Find special processes
        if (event.type == SDL_QUIT) {
            InputGatherer::addQuitEvent();
            continue;
        } else if (event.type == SDL_KEYDOWN && event.key.repeat != 0) {
            m_sdlEvents.erase(it);
            --it;
            continue;
        }

        // check if this is the right window
        unsigned windowID = (unsigned)-1;
        switch (event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                windowID = event.key.windowID;
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                windowID = event.button.windowID;
                break;
            case SDL_MOUSEWHEEL:
                windowID = event.wheel.windowID;
                break;
            case SDL_MOUSEMOTION:
                windowID = event.motion.windowID;
                break;
        }

        if (windowID != SDL_GetWindowID(m_window)) {
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
                if (event.wheel.y != 0) {
                    input.setMotion(InputKey::Motion::Scroll);
                    input.setKey(InputKey::Key::MouseOnly);
                    input.setScrollAmount(event.wheel.y); 
                }
                break;
        }

        // Set view intersections
        for (string& viewName : getSortedViews(m_views)) {
            const View& view = m_views.at(viewName);


            Pixel topLeft = view.getTopLeft();
            Pixel botRight = view.getBottomRight();

            if (mousePos.isBetween(topLeft, botRight)) {
                RelPixel relPos;

                relPos.setCol( 
                        (mousePos.getCol() - topLeft.getCol())
                        /(botRight.getCol() - topLeft.getCol())
                );

                relPos.setRow( 
                        (mousePos.getRow() - topLeft.getRow())
                        /(botRight.getRow() - topLeft.getRow())
                );

                Vector3D zeroPoint = view.getCamera().zeroPlaneIntersection(relPos);
                input.addViewIntersection(view.getName(), zeroPoint);
            }
        }

        InputGatherer::addInput(input);
        m_sdlEvents.erase(it);
        --it;
    }
}

Inputs SdlDisplayWindow::handleInputs(Inputs inputs) {

    for (string& viewName : getSortedViews(m_views)) {
        View& view = m_views.at(viewName);
        inputs = view.handleInputs(inputs);
    }

    return inputs;
}

void SdlDisplayWindow::setViewObjects(vector<Object> objects, string viewName) {

    if (m_views.count(viewName) > 0) {
        View& view = m_views.at(viewName);

        for (Object& object : objects) {
            SdlDrawable drawable = getSdlDrawableFrom(object,view);

            if (drawable.isInFrame == true){
                m_drawables.push_back(drawable);
            }
        }
    }
}

void SdlDisplayWindow::setViewTexts(std::vector<DrawableText> texts, std::string viewName) {

    if (m_views.count(viewName) > 0) {

        View& view = m_views.at(viewName);
        view.setDrawableText(texts);
    }
}



void SdlDisplayWindow::drawScreen() {

    // TODO clean this up and put it in functions/classes
    // TODO add in error catching
    // TODO use opengl to render so I can have skewed rectangles

    // Clear the screen by drawing it all black
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);


    std::sort(m_drawables.begin(), m_drawables.end(), 
            [](SdlDrawable& a, SdlDrawable& b) {
                if (a.viewLayer == b.viewLayer) {
                    return a.zPosition < b.zPosition;
                }
                else {
                    return a.viewLayer < b.viewLayer;
                }
            }
    );

    for (SdlDrawable& drawable : m_drawables) {

        // get the texture
        SDL_Texture* texture = m_sdlTextureManager.getTexture(drawable.imageFile);

        if (texture != NULL) {

            SDL_RenderCopyEx(m_renderer,
                    texture, &drawable.sourceRect, &drawable.destinationRect, 
                    drawable.angle*180.0/3.14159265359,
                    NULL, SDL_FLIP_NONE);
        }
        else {

            Animation& missing_animation = AnimationHandler::getAnimation(MISSING_ANIMATION);
            texture = m_sdlTextureManager.getTexture(missing_animation.getImageFile());
            SDL_RenderCopyEx(m_renderer,
                    texture, NULL, &drawable.destinationRect, 
                    drawable.angle*180.0/3.14159265359,
                    NULL, SDL_FLIP_NONE);
        }

    }

    // Get views by layer in desending order
    vector<string> sortedViews = getSortedViews(m_views);
    std::reverse(sortedViews.begin(), sortedViews.end());

    // Draw each view
    for (string& viewName: sortedViews) {

        View& view = m_views.at(viewName);
        view.clearCameraBounds();






        for (DrawableText& text : view.getTexts()) {

            SDL_Surface* surface = NULL;
            SDL_Texture* texture = NULL;
            SDL_Color color = toSdlColor(text.getColor());
            
            surface = TTF_RenderText_Solid(
                    SdlFontManager::getFont(text.getFont(), text.getFontSize()),
                    text.getText().c_str(),
                    color
            );

            if (surface == NULL){
                std::cerr << "input_surface TTF_RenderText error: " << SDL_GetError() << std::endl;
            }
            else {

                texture = SDL_CreateTextureFromSurface(m_renderer, surface);
                if (texture == NULL){
                    std::cerr << "input_texture SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
                    SDL_FreeSurface(surface);
                }
                else {

                    SDL_Rect dstRect = rectFrom(
                            text.getTopLeft(), 
                            text.getBottomRight(),
                            view.getBottomRight().getColInt() - view.getTopLeft().getColInt(), 
                            view.getBottomRight().getRowInt() - view.getTopLeft().getRowInt()
                    );

                    SDL_RenderCopy(m_renderer, texture, NULL, &dstRect);
                    SDL_FreeSurface(surface);
                    SDL_DestroyTexture(texture);
                }
            }
        } // Draw texts
    }

    SDL_RenderPresent(m_renderer);


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
