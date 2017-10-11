#ifndef SDL_HELPER_FUNCTIONS_H
#define SDL_HELPER_FUNCTIONS_H

#include "sdl_drawable.h"

#include "battle_room/common/input.h"
#include "battle_room/common/pixel.h"
#include "battle_room/common/rel_pixel.h"
#include "battle_room/common/color.h"
#include "battle_room/common/drawable_object.h"
#include "battle_room/common/drawable_text.h"
#include "battle_room/graphics/view.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

namespace BattleRoom {

    /**
     * \brief Utility function to get SDL rect from two pixel coordinates
     * \param topLeft Top-left corner of desired rect
     * \param bottomRight Bottom-right corner of desired rect
     * \return SDL_Rect made from the corners
     */
    SDL_Rect rectFrom(RelPixel topLeft, RelPixel bottomRight, px viewWidth, px viewHeight);

    /**
     * \brief Utility function to get SDL rect from two pixel coordinates
     * \param topLeft Top-left corner of desired rect
     * \param bottomRight Bottom-right corner of desired rect
     * \return SDL_Rect made from the corners
     */
    SDL_Rect rectFrom(Pixel topLeft, Pixel bottomRight);

    /**
     * \brief Retrieve the id of the window where event has occurred
     * \param event User input event that has occured
     * \return Window ID assigned by SDL
     */
    unsigned getWindowIdFrom(SDL_Event &event);

    /**
     * \brief Maps SDL_Keycode to InputKey::Key
     * \param code SDL_Keycode version of key
     * \return InputKey version of key
     */
    InputKey::Key sdlKeyToInputKey(SDL_Keycode code);

    /**
     * \brief Maps SDLMod to InputKey::Modifier
     * \param code SDLMod version of modifier
     * \return InputKey version of modifier
     */
    InputKey::Modifier sdlModifierToInputModifier(SDL_Keymod code);

    /**
     * \brief Maps an SDL_Mouse_event button and number of clicks to a InputKey::Key
     * \param key Button on the mouse that was pressed
     * \param clicks Number of times the button was pressed (greater than 1 is double click)
     * \return InputKey version of sdl_mouse button click
     */
    InputKey::Key sdlMouseButtonToInputKey(unsigned key, unsigned clicks);

    /**
     * \brief Maps Color class to SDL_Color
     * \param color Game version of color
     * \return SDL version of color
     */
    SDL_Color toSdlColor(Color color);

    /**
     * \brief Creates an instance drawable in SDL
     * \param object Animation object to be made into a drawable
     * \param view View that the object will be drawn on
     * \return Unique Pointer of SdlDrawable base class
     */
    UniqueDrawable getSdlDrawableFrom(const DrawableObject &object, View &view);

    /**
     * \brief Creates an instance drawable in SDL
     * \param object Text to be made into a drawable
     * \param view View that the text will be drawn on
     * \return Unique Pointer of SdlDrawable base class
     */
    UniqueDrawable getSdlDrawableFrom(const DrawableText &text, View &view);

} // BattleRoom namespace
#endif // SDL_HELPER_FUNCTIONS_H
