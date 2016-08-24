
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

/**
 * \brief SDL implementation of the DisplayWindow class
 * Initializes SDL, destroys the window, and quits SDL
 * Also manages SDL for multiple windows
 *
 */
class SdlWindow : public DisplayWindow {

public:

    // constructors

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

        // Clear the screen by drawing it all black
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

                // get needed values from the inputs
                Animation& animation = object.getAnimation();
                Vector3D& loc = object.position().location();
                Quaternion& ori = object.position().orientation();

                const Frame& frame = animation.getFrame(object.getAnimationState());
                const Pixel& frameTopLeft = frame.getTopLeft();
                const Pixel& frameBottomRight = frame.getBottomRight();

                double xScale = frame.getXScale();
                double yScale = frame.getYScale();

                // calculate world dimensions and coordinates of object
                meters objectWidth = xScale*(frameBottomRight.getCol() - frameTopLeft.getCol());
                meters objectHeight = yScale*(frameBottomRight.getRow() - frameTopLeft.getRow());

                // fix to get angle until I figure out the skewing issue
                // aka the camera must be facing straight down
                Vector3D rotatedX = ori.getRotated(Vector3D(1,0,0));
                double angle = 180.0*std::acos(rotatedX.x())*3.14156;
                Vector3D xOffset = Vector3D(objectWidth/2.0, 0, 0);
                Vector3D yOffset = Vector3D(0, objectHeight/2.0, 0);
                // real versions
                //Vector3D xOffset = ori.getRotated(Vector3D(objectWidth/2.0, 0, 0));
                //Vector3D yOffset = ori.getRotated(Vector3D(0, objectHeight/2.0, 0));
                // end fix

                RelPixel topLeftRel = camera.fromLocation(loc.minus(xOffset).plus(yOffset));
                RelPixel botRightRel = camera.fromLocation(loc.plus(xOffset).minus(yOffset));

                // get the unrotated versions?

                // Get pixel coordinates of texture
                SDL_Rect srcRect = rectFrom(frameTopLeft, frameBottomRight);
                SDL_Rect dstRect = rectFrom(topLeftRel, botRightRel, viewWidth, viewHeight);

                // get the texture
                SDL_Texture* texture = m_sdlTextureManager.getTexture(animation.getImageFile());

                // Render the texture
                SDL_RenderCopyEx(m_renderer,
                        texture, &srcRect, &dstRect, angle,
                        NULL, SDL_FLIP_NONE);

            }
        }

        SDL_RenderPresent(m_renderer);
    }

    /**
     * \brief Utility function to get SDL rect from two pixel coordinates
     * \param topLeft Top-left corner of desired rect
     * \param bottomRight Bottom-right corner of desired rect
     * \return SDL_Rect made from the corners
     */
    SDL_Rect rectFrom(RelPixel topLeft, RelPixel bottomRight, px viewWidth, px viewHeight) {

        SDL_Rect rect;
        rect.x = topLeft.getColInt(viewWidth);
        rect.y = topLeft.getRowInt(viewHeight);
        rect.w = bottomRight.getColInt(viewWidth) - rect.x;
        rect.h = bottomRight.getRowInt(viewHeight) - rect.y;

        return rect;
    }

    /**
     * \brief Utility function to get SDL rect from two pixel coordinates
     * \param topLeft Top-left corner of desired rect
     * \param bottomRight Bottom-right corner of desired rect
     * \return SDL_Rect made from the corners
     */
    SDL_Rect rectFrom(Pixel topLeft, Pixel bottomRight) {

        SDL_Rect rect;
        rect.x = topLeft.getColInt();
        rect.y = topLeft.getRowInt();
        rect.w = bottomRight.getColInt() - rect.x;
        rect.h = bottomRight.getRowInt() - rect.y;

        return rect;
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

    SdlTextureManager m_sdlTextureManager; ///< Manages textures using the SDL Renderer
    SDL_Renderer* m_renderer; ///< Reads in textures and draws everything
    SDL_Window* m_window; ///< SDL Window Pointer

    std::unordered_map<string,View> m_views; ///< Container for views

    int m_windowCount = 0; ///< If this gets to zero, it quits SDL

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
