#ifndef SDL_DISPLAY_WINDOW
#define SDL_DISPLAY_WINDOW

#include "battle_room/graphics/display_window.h"
#include "sdl_texture_manager.h"
#include "sdl_drawable.h"

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
    void gatherInputs() override;
    void addViewObjects(std::vector<DrawableObject> objects, std::string viewName) override;
    void addViewTexts(std::vector<DrawableText> texts, std::string viewName) override;
    void drawScreen() override;
    void addView(View view) override;
    Inputs handleInputs(Inputs inputs) override; 

private:

    SdlTextureManager m_sdlTextureManager; ///< Manages textures using the SDL Renderer
    SDL_Renderer* m_renderer; ///< Reads in textures and draws everything
    SDL_Window* m_window; ///< SDL Window Pointer

    std::unordered_map<std::string,View> m_views; ///< Container for views

    bool m_drawingA = true; ///< Switches between drawables for multithreading
    std::vector<UniqueDrawable> m_drawablesA; ///< Container for drawables
    std::vector<UniqueDrawable> m_drawablesB; ///< Container for drawables

    static std::vector<SDL_Event> m_sdlEvents;
    static int m_windowCount; ///< If this gets to zero, it quits SDL
    static int m_windowsDrawn; // TODO figure out a better way

}; // SdlWindow class
} // BattleRoom namespace
#endif // SDL_DISPLAY_WINDOW
