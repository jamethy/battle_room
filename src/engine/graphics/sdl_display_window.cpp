
#include "battle_room/engine/graphics/display_window.h"
#include "battle_room/common/resource_descriptor.h"

#include "sdl_texture_manager.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <string>
#include <map>
#include <iostream>
#include <exception>

using std::string;
using std::map;
using std::vector;

namespace BattleRoom {

class SdlWindow : public DisplayWindow {

public:

    SdlWindow(string settingsFile) {

        string name = "name";
        int width = 250;
        int height = 250;

        // read in settings file
        ResourceDescriptor settings = ResourceDescriptor::readFile(settingsFile);

        ResourceDescriptor sub = settings.getSubResource("Name");
        if (!sub.getKey().empty()) {
            name = sub.getValue();
        }

        sub = settings.getSubResource("Width");
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


    Inputs getInputs() override {
        //SDL_Event event;
        //SDL_GetTicks();
        //while (SDL_PollEvent(&event) {
        return Inputs();
    }

    void addWorldObjects(vector<Object> objects) override {
        
        //if (!m_textureMap.contains(object.getTexture()) {
                //SDL_Texture* texture = IMG_LoadTexture(m_renderer, object.getTexture().c_str());
        //}
    }

    void addUiObjects(vector<Object> objects) override {
    }

    void addMenuObjects(vector<Object> objects) override {
    }

    void drawScreen() override {
        //SDL_SetRenderDrawColor();
    }

    TextureManager& getTextureManager() override {
        return m_sdlTextureManager;
    }

private:

    SdlTextureManager m_sdlTextureManager;
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;

    int m_windowCount = 0;

}; // SdlWindow class


UniqueDisplayWindow createDisplayWindow(string settingsFilename) {

    try
    {
        return UniqueDisplayWindow(new SdlWindow(settingsFilename));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

} // BattleRoom namespace
