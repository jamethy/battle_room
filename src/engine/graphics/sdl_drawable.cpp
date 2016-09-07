
#include "sdl_drawable.h"

namespace BattleRoom {

SdlDrawable::SdlDrawable() {}
SdlDrawable::~SdlDrawable() {}

// getters and setters

bool SdlDrawable::isInFrame() {
     return m_isInFrame;
}

int SdlDrawable::getViewLayer() {
     return m_viewLayer;
}

meters SdlDrawable::getZPosition() {
     return m_zPosition;
}

radians SdlDrawable::getAngle() {
    return m_angle;
}

SDL_Rect SdlDrawable::getDestinationRect() {
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

void SdlDrawable::setDestinationRect(SDL_Rect destinationRect) {
    m_destinationRect = destinationRect;
}

} // namespace BattleRoom
