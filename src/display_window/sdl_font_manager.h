#ifndef BATTLE_ROOM_SDL_FONT_MANAGER
#define BATTLE_ROOM_SDL_FONT_MANAGER

#include "SDL.h"
#include "SDL_ttf.h"

#include <string>

namespace BattleRoom {

/**
 * Creates and destroys SDL_Fonts
 */
    class SdlFontManager {

    public:

        /**
         * \brief Gets the SDL_Font from the font key
         * \para fontKey Key to font (filepath relative to res/fonts/ directory)
         * \return Pointer to the font
         */
        static TTF_Font *getFont(std::string fontKey, int size);

        /**
         * \brief Destroys all the fonts that have been loaded
         */
        static void clear();

    }; // SdlFontManager class
} // BattleRoom namespace
#endif // BATTLE_ROOM_SDL_FONT_MANAGER
