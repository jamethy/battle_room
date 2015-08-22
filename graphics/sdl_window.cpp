#include "sdl_window.h"
#include "object_handler.h"

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

    m_window = SDL_CreateWindow("deathblade_floating", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr){
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr){
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        throw std::exception();
    }
}

SDLWindowClass::~SDLWindowClass()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLWindowClass::update()
{
    ObjectHandlerClass* objs = ObjectHandlerClass::Instance();
    objs->update();


    SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);
    SDL_RenderClear(m_renderer);




    SDL_RenderPresent(m_renderer);

}

void SDLWindowClass::draw_object(DrawableObjectClass &obj)
{
    /*SDL_Texture* obj_texture = (SDL_Texture*)obj.getTexture();
    if(obj_texture == NULL) return;

    SDL_Rect dst = camera->calculate_display_destination(
                x,
                y,
                texturewidth,
                textureheight,
                zplane);

    SDL_RenderCopyEx(m_renderer, obj_texture, NULL, &dst, (th-camera->camyaw)*180.0/3.14159265359, NULL, SDL_FLIP_NONE);
*/
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
    return IMG_LoadTexture(m_renderer, resource.c_str());
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
