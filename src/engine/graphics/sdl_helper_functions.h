#ifndef SDL_HELPER_FUNCTIONS_H
#define SDL_HELPER_FUNCTIONS_H

#include "battle_room/common/input.h"
#include "battle_room/common/pixel.h"
#include "battle_room/common/rel_pixel.h"
#include "battle_room/common/color.h"

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


InputKey::Key sdlKeyToInputKey(SDL_Keycode code);

InputKey::Key sdlMouseButtonToInputKey(unsigned key, unsigned clicks);

SDL_Color toSdlColor(Color color);

} // BattleRoom namespace
#endif // SDL_HELPER_FUNCTIONS_H
