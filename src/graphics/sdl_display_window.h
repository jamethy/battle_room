#ifndef SDL_DISPLAY_WINDOW
#define SDL_DISPLAY_WINDOW

#include "battle_room/graphics/display_window.h"
#include "battle_room/graphics/view.h"
#include "sdl_texture_manager.h"
#include "sdl_drawable.h"

#include <unordered_map>

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

        void addViewObjects(const std::vector<DrawableObject> &objects, std::string viewName) override;

        void addViewTexts(const std::vector<DrawableText> &texts, std::string viewName) override;

        void addViewMenus(const std::vector<DrawableMenu> menus, std::string viewName) override;

        void drawScreen() override;

        void switchBuffers() override;

        Inputs handleInputs(Inputs inputs) override;

    private:

        /**
         * \brief Tries to smartly resize the views
         * \param oldWidth New width of window
         * \param oldHeight New height of window
         */
        void resizeViews(int oldWidth, int oldHeight);

        SdlTextureManager m_sdlTextureManager; ///< Manages textures using the SDL Renderer
        SDL_Renderer *m_renderer; ///< Reads in textures and draws everything
        SDL_Window *m_window; ///< SDL Window Pointer
        std::string m_windowName; ///< Name and title of window

        std::unordered_map<std::string, View> m_views; ///< Container for views

        bool m_drawingA = true; ///< Switches between drawables for multithreading
        std::vector<UniqueDrawable> m_drawablesA; ///< Container for drawables
        std::vector<UniqueDrawable> m_drawablesB; ///< Container for drawables

        // Track the mouse position by updating when available
        Pixel m_mousePos;
        int m_windowWidth = 1500;
        int m_windowHeight = 1000;

        static std::vector<SDL_Event> m_sdlEvents;
        static int m_windowCount; ///< If this gets to zero, it quits SDL
        static int m_windowsDrawn; // TODO figure out a better way
        static unsigned m_windowWithFocus;

    }; // SdlWindow class
} // BattleRoom namespace
#endif // SDL_DISPLAY_WINDOW
