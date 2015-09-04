#include "sdl_window.h"
#include "sdl_animations.h"
#include "object_handler.h"
#include "graphics_layer.h"

#include <iostream>
#include <memory>
#include <exception>

namespace GraphicsInterface {


GraphicsWindowClass::~GraphicsWindowClass(){}

UniqueGraphicsWindow createWindow(unsigned width, unsigned height)
{
    try
    {
        return UniqueGraphicsWindow(new SDLWindowClass(width,height));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

SDLWindowClass::SDLWindowClass(unsigned width, unsigned height)
    : m_camera(CameraClass(width,height))
{
    if(SDL_WasInit(SDL_INIT_EVERYTHING) == 0)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
            throw std::exception();
        }
    }
    if(TTF_WasInit() == 0)
    {
        if (TTF_Init() != 0){
            std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            throw std::exception();
        }
    }

    m_window = UniqueWindow(SDL_CreateWindow("deathblade_floating", 0, 0, width, height, SDL_WINDOW_SHOWN),SDL_Deleter());
    if (m_window == nullptr){
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
    }

    m_renderer = UniqueRenderer(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED),SDL_Deleter());
    if (m_renderer == nullptr){
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
    }
    ++sdl_window_count;
}


int SDLWindowClass::sdl_window_count = 0;

SDLWindowClass::~SDLWindowClass()
{
    if(--sdl_window_count <= 0)
    {
        TTF_Quit();
        SDL_Quit();
    }
}



void SDLWindowClass::setViewBounds(Utility::vec2d& worldMin, Utility::vec2d& worldMax)
{
    m_camera.setCameraBounds(worldMin,worldMax);
}

CameraObjectClas *SDLWindowClass::getCamera()
{
    return &m_camera;
}



void SDLWindowClass::update(const double &gameTime)
{
    checkWindowSize();

    ObjectHandlerClass* objectHandler = ObjectHandlerClass::Instance();
    objectHandler->update();


    SDL_SetRenderDrawColor(m_renderer.get(), 0,0,0,255);
    SDL_RenderClear(m_renderer.get());

    for (GraphicsLayer* obj : *objectHandler) draw_object(*obj, gameTime);

    SDL_RenderPresent(m_renderer.get());

}

void SDLWindowClass::draw_object(GraphicsLayer &obj, double drawTime)
{
    SDLAnimationClass* animation = (SDLAnimationClass*)obj.getAnimation(drawTime);
    if(animation != nullptr) animation->renderOn(m_renderer.get(), m_camera.getZeroCalculator());
}


void SDLWindowClass::checkWindowSize()
{
    static int oldWidth = 0;
    static int oldHeight = 0;
    int newWidth = 0;
    int newHeight = 0;
    SDL_GetWindowSize(m_window.get(), &newWidth, &newHeight);
    if(newWidth != oldWidth || newHeight != oldHeight)
    {
        oldWidth = newWidth;
        oldHeight = newHeight;
        m_camera.setWindowSize(newWidth, newHeight);
    }
}



}
