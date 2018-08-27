#ifndef SDL_DRAWABLE_H
#define SDL_DRAWABLE_H

#include "sdl_texture_manager.h"

#include "resource.h" // just for meters/radians

#include "SDL_image.h"
#include "SDL.h"

#include <string>
#include <memory>

namespace BattleRoom {

    class SdlDrawable {

    public:

        // constructors
        SdlDrawable();

        virtual ~SdlDrawable();

        /**
         * \brief Draws the drawable object given the texture manager
         * \param textureManager Something with textures in it
         */
        virtual void draw(SdlTextureManager &textureManager) = 0;


        // getters and setters

        bool isInFrame() const;

        int getViewLayer() const;

        meters getZPosition() const;

        radians getAngle() const;

        SDL_RendererFlip getFlip() const;

        SDL_Rect getDestinationRect() const;

        void setIsInFrame(bool isInFrame);

        void setViewLayer(int viewLayer);

        void setZPosition(meters zPosition);

        void setAngle(radians angle);

        void setFlip(SDL_RendererFlip flip);

        void setDestinationRect(SDL_Rect destinationRect);

    private:

        bool m_isInFrame = false; ///< If not in frame, values invalid
        int m_viewLayer = 0; ///< Layer of drawn view for sorting
        meters m_zPosition = 0; ///< Z position for sorting
        radians m_angle = 0; ///< Angle to draw texture at
        SDL_RendererFlip m_flip = SDL_FLIP_NONE;
        SDL_Rect m_destinationRect; ///< Clip of screen (not view) to draw on

    }; // SdlDrawable class

    typedef std::unique_ptr<SdlDrawable> UniqueDrawable;

} // BattleRoom namespace
#endif // SDL_DRAWABLE_H

