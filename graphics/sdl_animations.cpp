#include "sdl_animations.h"

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
    m_starttime(Utility::TimeBase::getTime()),
    m_duration(duration)
{

}

void SDLAnimationClass::setPlayerPos(Utility::vec2d& pos, double th)
{
    m_playerPos = pos;
    m_playerTh = th;
}

Utility::vec2d& SDLAnimationClass::getPlayerPos(){ return m_playerPos; }
double SDLAnimationClass::getPlayerTh(){ return m_playerTh; }

typedef std::map<SDL_Renderer*, UniqueTexture> TextureMap;

////// PlayerAnimation //////////////////////////////////////////////////////////////////////
////// PlayerAnimation //////////////////////////////////////////////////////////////////////
////// PlayerAnimation //////////////////////////////////////////////////////////////////////
class PlayerAnimation : public SDLAnimationClass
{
public:
    PlayerAnimation(double duration): SDLAnimationClass(duration){}
    virtual ~PlayerAnimation(){}

    static TextureMap textureMap;
    double playerWidth = 0.1;
    double playerHeight = 0.1;
    Utility::vec2d PlayerCenter;
};

TextureMap PlayerAnimation::textureMap = TextureMap();

class PlayerNoAnimation : public PlayerAnimation
{
public:
    PlayerNoAnimation() : PlayerAnimation(0) {}
    ~PlayerNoAnimation(){}
    void update(double time){}
    bool isComplete(){ return false; }
    AnimationType after(){ return NoAnimation; }

    void renderOn(SDL_Renderer* renderer, CameraClass& cam)
    {
        SDL_Texture* texture = PlayerAnimation::textureMap[renderer].get();
        if(texture == nullptr) PlayerAnimation::textureMap[renderer] = getUniqueTexture(renderer, "initialstar.png");

        ScreenPos sp = cam.posFromWorld(getPlayerPos());

        SDL_Rect dst_rect;
        dst_rect.x = sp.x();
        dst_rect.y = sp.y();
        dst_rect.w = cam.wFromWorld(playerWidth);
        dst_rect.h = cam.hFromWorld(playerHeight);


        SDL_Point center;
        center.x = cam.wFromWorld(PlayerCenter.x());
        center.y = cam.hFromWorld(PlayerCenter.y());

        SDL_RenderCopyEx(renderer,
                        texture,
                        src_rect,
                        &dst_rect,
                        getPlayerTh(),
                        &center, SDL_FLIP_NONE);
    }
    SDL_Rect* src_rect = nullptr;
};


////// StarAnimation //////////////////////////////////////////////////////////////////////
////// StarAnimation //////////////////////////////////////////////////////////////////////
////// StarAnimation //////////////////////////////////////////////////////////////////////

class StarAnimation : public SDLAnimationClass
{
public:
    StarAnimation(double duration): SDLAnimationClass(duration){}
    virtual ~StarAnimation(){}

    static TextureMap textureMap;
    double playerWidth = 0.1;
    double playerHeight = 0.1;
    Utility::vec2d PlayerCenter;
};

TextureMap StarAnimation::textureMap = TextureMap();


class StarNoAnimation : public StarAnimation
{
public:
    StarNoAnimation() : StarAnimation(0) {}
    ~StarNoAnimation(){}
    void update(double time){}
    bool isComplete(){ return false; }
    AnimationType after(){ return NoAnimation; }

    void renderOn(SDL_Renderer* renderer, CameraClass& cam)
    {
        SDL_Texture* texture = StarAnimation::textureMap[renderer].get();
        if(texture == nullptr) StarAnimation::textureMap[renderer] = getUniqueTexture(renderer, "initialcharacter.png");

        ScreenPos sp = cam.posFromWorld(getPlayerPos());

        SDL_Rect dst_rect;
        dst_rect.x = sp.x();
        dst_rect.y = sp.y();
        dst_rect.w = cam.wFromWorld(playerWidth);
        dst_rect.h = cam.hFromWorld(playerHeight);


        SDL_Point center;
        center.x = cam.wFromWorld(PlayerCenter.x());
        center.y = cam.hFromWorld(PlayerCenter.y());

        SDL_RenderCopyEx(renderer,
                        texture,
                        src_rect,
                        &dst_rect,
                        getPlayerTh(),
                        &center, SDL_FLIP_NONE);
    }
    SDL_Rect* src_rect = nullptr;
};



////// Create Functions //////////////////////////////////////////////////////////////////////
////// Create Functions //////////////////////////////////////////////////////////////////////
////// Create Functions //////////////////////////////////////////////////////////////////////
UniqueAnimation createPlayerAnimation(AnimationType animation)
{
    switch (animation) {
    case NoAnimation:
        return UniqueAnimation(new PlayerNoAnimation());
    default:
        return UniqueAnimation(new PlayerNoAnimation());
    }
}

UniqueAnimation createStarAnimation(AnimationType animation)
{
    switch (animation) {
    case NoAnimation:
        return UniqueAnimation(new StarNoAnimation());
    default:
        return UniqueAnimation(new StarNoAnimation());
    }
}

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
