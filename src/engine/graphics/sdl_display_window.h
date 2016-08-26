#ifndef SDL_DISPLAY_WINDOW
#define SDL_DISPLAY_WINDOW

#include "battle_room/engine/graphics/display_window.h"
#include "sdl_texture_manager.h"

namespace BattleRoom {

/**
 * \brief SDL implementation of the DisplayWindow class
 * Initializes SDL, destroys the window, and quits SDL
 * Also manages SDL for multiple windows
 *
 */
class SdlDisplayWindow : public DisplayWindow {

public:

    // constructors

    SdlDisplayWindow(ResourceDescriptor settings);
    ~SdlDisplayWindow();

    // inherited
    void applySettings(ResourceDescriptor settings) override;
    Inputs getInputs() override;
    void addObjectsToView(std::vector<Object> objects, std::string viewName) override;
    void drawScreen() override;
    void addView(View view) override;
    void setCameraMapReference(std::unordered_map<std::string,Camera>& cameraMap) override;

private:

    SdlTextureManager m_sdlTextureManager; ///< Manages textures using the SDL Renderer
    SDL_Renderer* m_renderer; ///< Reads in textures and draws everything
    SDL_Window* m_window; ///< SDL Window Pointer

    std::unordered_map<std::string,View> m_views; ///< Container for views
    std::unordered_map<std::string,Camera>& m_cameras; ///< Reference to camera map

    static int m_windowCount; ///< If this gets to zero, it quits SDL

}; // SdlWindow class
} // BattleRoom namespace
#endif // SDL_DISPLAY_WINDOW
