#include "sdl_animations.h"
#include "animation_player.h"
#include "animation_star.h"

#include "../utility/br_time.h"

#include <map>

namespace GraphicsInterface {

////// Useful Functions //////////////////////////////////////////////////////////////////////
////// Useful Functions //////////////////////////////////////////////////////////////////////
////// Useful Functions //////////////////////////////////////////////////////////////////////

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

UniqueTexture getUniqueTexture(SDL_Renderer* renderer, std::string str)
{
    std::string path = getResourcePath("") + str;
    return UniqueTexture(IMG_LoadTexture(renderer, path.c_str()), SDL_Deleter());
}



////// SDLAnimationClass //////////////////////////////////////////////////////////////////////
////// SDLAnimationClass //////////////////////////////////////////////////////////////////////
////// SDLAnimationClass //////////////////////////////////////////////////////////////////////
SDLAnimationClass::SDLAnimationClass(double duration) :
    m_starttime(Utility::getTime()),
    m_duration(duration)
{

}

void SDLAnimationClass::setPosition(Utility::vec2d& pos, double th)
{
    m_position = pos;
    m_th = th;
}

Utility::vec2d& SDLAnimationClass::getPosition(){ return m_position; }
double SDLAnimationClass::getTheta(){ return m_th; }

////// Create Functions //////////////////////////////////////////////////////////////////////
////// Create Functions //////////////////////////////////////////////////////////////////////
////// Create Functions //////////////////////////////////////////////////////////////////////

UniqueAnimation createAnimation(ObjectType obj, AnimationType animation)
{
    switch (obj) {
    case Player:
        return createPlayerAnimation(animation);
    case Star:
        return createStarAnimation(animation);
    default:
        return UniqueAnimation(nullptr);
    }
}

} // GraphicsInterface namespace
