#ifndef BATTLE_ROOM_SDL_DISPLAY_WINDOW
#define BATTLE_ROOM_SDL_DISPLAY_WINDOW

#include "display_window/display_window.h"
#include "display_window/sdl_texture_manager.h"
#include "display_window/sdl_drawable.h"

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
        explicit SdlDisplayWindow(ResourceDescriptor settings);

        ~SdlDisplayWindow() override;

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        void gatherInputs(const std::vector<UniqueInterface> &views) override;

        void addViewDrawables(ViewInterface *view) override;

        void drawScreen() override;

        void switchBuffers() override;

        const UniqueId getUniqueId() const override;

        std::string getName() const override;

        int getWidth() const override;

        int getHeight() const override;

        TextureManager *getTextureManager() override;

    private:

        /**
         * \brief Tries to smartly resize the views
         * \param oldWidth New width of window
         * \param oldHeight New height of window
         */
        void resizeViews(int oldWidth, int oldHeight, const std::vector<UniqueInterface> &views);

        SdlTextureManager m_sdlTextureManager; ///< Manages textures using the SDL Renderer
        SDL_Renderer *m_renderer; ///< Reads in textures and draws everything
        SDL_Window *m_window; ///< SDL Window Pointer
        std::string m_windowName; ///< Name and title of window

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

        UniqueId m_uniqueId;

    }; // SdlWindow class
} // BattleRoom namespace
#endif // BATTLE_ROOM_SDL_DISPLAY_WINDOW
