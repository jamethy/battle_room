#include "sdl_window.h"
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
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        throw std::exception();
    }

    if (TTF_Init() != 0){
        std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
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
}

SDLWindowClass::~SDLWindowClass()
{
    SDL_Quit();
}

void SDLWindowClass::update()
{
    ObjectHandlerClass* objs = ObjectHandlerClass::Instance();
    objs->update();


    SDL_SetRenderDrawColor(m_renderer.get(), 0,0,0,255);
    SDL_RenderClear(m_renderer.get());




    SDL_RenderPresent(m_renderer.get());

}

bool SDLWindowClass::draw_object(GraphicsLayer &obj)
{
    SDL_Texture* obj_texture = getTexture(obj.getType());
    if(obj_texture == NULL) return;

    Utility::vec2d pos = obj.getPos();
    double th = obj.getTh();

    SDL_Rect dst; // = getFromCamera(pos,th)
    double TH; // getFromCamera(th)

    return SDL_RenderCopyEx(m_renderer,
                            obj_texture, NULL, &dst,
                            TH,
                            NULL, SDL_FLIP_NONE) != 0;
}

SDL_Texture *SDLWindowClass::getTexture(ObjectType object_type)
{
    unsigned int obj_pos = (unsigned)object_type;

    if( obj_pos >= m_textures.size())
        m_textures.resize(obj_pos);

    SDL_Texture* texture = m_textures[obj_pos].get();

    if(texture == nullptr)
    {
        m_textures[obj_pos] = UniqueTexture(loadTexture(object_type),SDL_Deleter());
        texture = m_textures[obj_pos].get();
    }
    return texture;
}




SDL_Texture* SDLWindowClass::loadTexture(ObjectType object_type)
{
    std::string resource = "";
    switch (object_type) {
    case Player:
        resource = getResourcePath() + "initialcharacter.png";
        break;
    case Star:
        resource = getResourcePath() + "initialcharacter.png";
        break;
    default:
        return nullptr;
    }
    return IMG_LoadTexture(m_renderer.get(), resource.c_str());
}

std::string getResourcePath(const std::string &subDir){
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif
    static std::string baseRes;
    if (baseRes.empty()){
        char *basePath = SDL_GetBasePath();
        if (basePath){
            baseRes = basePath;
            SDL_free(basePath);
        }
        else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        //We replace the last bin/ with res/ to get the the resource path
        size_t pos = baseRes.rfind("bin");
        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}


}
