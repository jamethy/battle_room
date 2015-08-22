#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "../interfaces/graphics_interface.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <vector>

namespace GraphicsInterface
{

struct SDL_Deleter
{
  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

typedef std::unique_ptr<SDL_Texture,SDL_Deleter> UniqueTexture;

class SDLWindowClass : public GraphicsWindowClass
{
public:
    SDLWindowClass(unsigned width, unsigned height);
    ~SDLWindowClass();
    void update();

private:

    void draw_object(DrawableObjectClass& obj);

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    SDL_Texture* loadTexture(ObjectType object_type);
    SDL_Texture *getTexture(ObjectType object_type);
    std::vector<UniqueTexture> m_textures;
};


std::string getResourcePath(const std::string &subDir = "");

}

#endif // SDL_WINDOW_H
