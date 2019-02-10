
#include "display_window/sdl_drawable.h"

namespace BattleRoom {

    SdlDrawable::SdlDrawable() {}

    SdlDrawable::~SdlDrawable() {}

// getters and setters

    bool SdlDrawable::isInFrame() const {
        return m_isInFrame;
    }

    int SdlDrawable::getViewLayer() const {
        return m_viewLayer;
    }

    meters SdlDrawable::getZPosition() const {
        return m_zPosition;
    }

    radians SdlDrawable::getAngle() const {
        return m_angle;
    }

    SDL_RendererFlip SdlDrawable::getFlip() const {
        return m_flip;
    }

    SDL_Rect SdlDrawable::getDestinationRect() const {
        return m_destinationRect;
    }

    void SdlDrawable::setIsInFrame(bool isInFrame) {
        m_isInFrame = isInFrame;
    }

    void SdlDrawable::setViewLayer(int viewLayer) {
        m_viewLayer = viewLayer;
    }

    void SdlDrawable::setZPosition(meters zPosition) {
        m_zPosition = zPosition;
    }

    void SdlDrawable::setAngle(radians angle) {
        m_angle = angle;
    }

    void SdlDrawable::setFlip(SDL_RendererFlip flip) {
        m_flip = flip;
    }

    void SdlDrawable::setDestinationRect(SDL_Rect destinationRect) {
        m_destinationRect = destinationRect;
    }

} // namespace BattleRoom
