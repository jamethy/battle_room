
#include "battle_room/engine/graphics/display_window.h"
#include "battle_room/common/resource_descriptor.h"

#include "sdl_texture_manager.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <cmath>
#include <string>
#include <unordered_map>
#include <iostream>
#include <exception>

using std::string;
using std::vector;

namespace BattleRoom {

class SdlWindow : public DisplayWindow {

public:
    SdlWindow(ResourceDescriptor settings)
    {
        // read in settings
        string name = "name";
        int width = 500;
        int height = 500;

        if (!settings.getValue().empty()) {
            name = settings.getValue();
        }

        ResourceDescriptor sub = settings.getSubResource("Width");
        if (!sub.getKey().empty()) {
            width = stoi(sub.getValue());
        }

        sub = settings.getSubResource("Height");
        if (!sub.getKey().empty()) {
            height = stoi(sub.getValue());
        }


        // TODO throw exceptions instead of cerr
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        }

        if (TTF_Init() != 0){
            std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }

        m_window = SDL_CreateWindow(name.c_str(), 0, 0, width, height,SDL_WINDOW_SHOWN);
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
    }

    ~SdlWindow() {

        m_sdlTextureManager.clear();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);

        if (--m_windowCount <= 0) {
            SDL_Quit();
        }
    }


    // TODO fill this function with something meaningful
    // TODO make a SDL Inputs map class
    Inputs getInputs() override {

        Inputs inputs;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_KEYDOWN) {

                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        inputs.m_quit = true;
                        break;
                    default:
                        break;
                }
            }
            else if (event.type == SDL_QUIT) {
                inputs.m_quit = true;
            }
        }

        return inputs;
    }

    void addObjectsToView(vector<Object> objects, string viewName) override {
        
        if (m_views.count(viewName) > 0) {

            View& view = m_views.at(viewName);
            view.addObjects(objects);
        }
        else {
            // throw exception?
        }
    }

    void drawScreen() override {

        // TODO clean this up and put it in functions/classes
        // TODO add in error catching
        // TODO use opengl to render so I can have skewed rectangles


        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);

        // draw objects
        for (std::pair<string,View> viewEntry : m_views) {

            View& view = viewEntry.second;

            Pixel topLeft = view.getTopLeft();
            Pixel bottomRight = view.getBottomRight();
            px viewWidth = bottomRight.getColInt() - topLeft.getColInt();
            px viewHeight = bottomRight.getRowInt() - topLeft.getRowInt();
            Camera& camera = view.getCamera();

            for (Object& object : view.getObjects()) {

                Animation& animation = object.getAnimation();
                seconds animationState = object.getAnimationState();
                Position& pos = object.position();
                Vector3D& loc = pos.location();
                Quaternion& ori = pos.orientation();


                const Frame& frame = animation.getFrame(animationState);
                const Pixel& frameTopLeft = frame.getTopLeft();
                const Pixel& frameBottomRight = frame.getBottomRight();

                double xScale = frame.getXScale();
                double yScale = frame.getYScale();

                meters objectWidth = xScale*(frameBottomRight.getCol() - frameTopLeft.getCol());
                meters objectHeight = yScale*(frameBottomRight.getRow() - frameTopLeft.getRow());

                Vector3D xOffset = ori.getRotated(Vector3D(objectWidth/2.0, 0, 0));
                Vector3D yOffset = ori.getRotated(Vector3D(0, objectHeight/2.0, 0));

                Vector3D topLeftV = loc.minus(xOffset).plus(yOffset);
                Vector3D botRightV = loc.plus(xOffset).minus(yOffset);

                RelPixel topLeftRel = camera.fromLocation(topLeftV);
                RelPixel botRightRel = camera.fromLocation(botRightV);

                SDL_Texture* texture = m_sdlTextureManager.getTexture(animation.getImageFile());
                SDL_Rect srcRect;
                srcRect.x = frameTopLeft.getColInt();
                srcRect.y = frameTopLeft.getRowInt();
                srcRect.w = frameBottomRight.getColInt() - srcRect.x;
                srcRect.h = frameBottomRight.getRowInt() - srcRect.y;

                SDL_Rect dstRect;
                dstRect.x = topLeftRel.getColInt(viewWidth);
                dstRect.y = topLeftRel.getRowInt(viewHeight);
                dstRect.w = botRightRel.getColInt(viewWidth) - dstRect.x;
                dstRect.h = botRightRel.getRowInt(viewHeight) - dstRect.y;

                // fix to get angle until I figure out the skewing issue
                Vector3D x(1,0,0);
                Vector3D rotatedX = ori.getRotated(x);
                double angle = std::acos(x.dot(rotatedX));

                SDL_RenderCopyEx(m_renderer,
                        texture, &srcRect, &dstRect, angle,
                        NULL, SDL_FLIP_NONE);

            }
        }

        SDL_RenderPresent(m_renderer);
    }

    void addView(View view) override {

        string name = view.getName();

        if (m_views.count(name) > 0) {
            m_views.at(name) = view;
        }
        else {
            m_views.insert(std::pair<string,View>(name,view));
        }
    }

    TextureManager& getTextureManager() override {
        return m_sdlTextureManager;
    }

private:

    SdlTextureManager m_sdlTextureManager;
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;

    std::unordered_map<string,View> m_views;

    int m_windowCount = 0;

}; // SdlWindow class


UniqueDisplayWindow createDisplayWindow(ResourceDescriptor settings) {

    try
    {
        return UniqueDisplayWindow(new SdlWindow(settings));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

} // BattleRoom namespace
