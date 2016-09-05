#ifndef SDL_DRAWABLE_H
#define SDL_DRAWABLE_H

#include "battle_room/common/resource.h" // just for meters/radians

#include "SDL_image.h"
#include "SDL.h"

#include <string>

namespace BattleRoom {

struct SdlDrawable {

    bool isInFrame = false; ///< If not in frame, values invalid
    int viewLayer = 0; ///< Layer of drawn view for sorting
    meters zPosition = 0; ///< Z position for sorting
    radians angle = 0; ///< Angle to draw texture at
    SDL_Rect sourceRect; ///< Clip of texture for sprite
    SDL_Rect destinationRect; ///< Clip of screen (not view) to draw on
    std::string imageFile; ///< Image sprite file

}; // SdlDrawable struct
} // BattleRoom namespace
#endif // SDL_DRAWABLE_H

