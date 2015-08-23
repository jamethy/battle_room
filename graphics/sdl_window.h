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

typedef std::unique_ptr<SDL_Window,SDL_Deleter> UniqueWindow;
typedef std::unique_ptr<SDL_Texture,SDL_Deleter> UniqueTexture;
typedef std::unique_ptr<SDL_Renderer,SDL_Deleter> UniqueRenderer;

class SDLWindowClass : public GraphicsWindowClass
{
public:
    SDLWindowClass(unsigned width, unsigned height);
    ~SDLWindowClass();
    void update();

private:

    bool draw_object(GraphicsLayer &obj);

    UniqueWindow m_window;
    UniqueRenderer m_renderer;

    SDL_Texture* loadTexture(ObjectType object_type);
    SDL_Texture *getTexture(ObjectType object_type);
    std::vector<UniqueTexture> m_textures;
};


std::string getResourcePath(const std::string &subDir = "");

}

#endif // SDL_WINDOW_H
