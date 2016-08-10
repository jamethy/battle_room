
#include "battle_room/engine/graphics/display_window.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <string>
#include <map>
#include <iostream>

using std::string;
using std::map;
using std::vector;

using Common::Inputs;
using Common::Object;

namespace Graphics {

class SdlWindow : public DisplayWindow {

public:

    SdlWindow(string settingsFile) {

        // read in settings file
        string name = "name";
        int width = 250;
        int height = 250;

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
    }

    ~SdlWindow() {
//        for (std::pair<string,SDL_Texture*> texture : m_textureMap) {
//            SDL_DestroyTexture(texture->second);
//        }
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }


    Inputs getInputs() {
        //SDL_Event event;
        //SDL_GetTicks();
        //while (SDL_PollEvent(&event) {
        return Inputs();
    }

    void addWorldObjects(vector<Object> objects) {
        
        //if (!m_textureMap.contains(object.getTexture()) {
                //SDL_Texture* texture = IMG_LoadTexture(m_renderer, object.getTexture().c_str());
        //}
    }

    void addUiObjects(vector<Object> objects) {
    }

    void addMenuObjects(vector<Object> objects) {
    }

    void drawScreen() {
        //SDL_SetRenderDrawColor();
    }

private:

    SDL_Renderer* m_renderer;
    SDL_Window* m_window;

    map<string,SDL_Texture*> m_textureMap;

}; // SdlWindow class


DisplayWindow* createDisplayWindow(string settingsFilename) {
    return new SdlWindow(settingsFilename);
}

} // Graphics namespace
