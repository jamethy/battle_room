#include "battle_room/engine/animation/view.h"

#include <cmath>

namespace BattleRoom {

void View::applySettings(ResourceDescriptor settings) {

    if (isNotEmpty(settings.getValue())) {
        setName(settings.getValue());
    }

    m_topLeft.applySettings( settings.getSubResource("TopLeft") );
    m_bottomRight.applySettings( settings.getSubResource("BottomRight") );
    m_camera.applySettings( settings.getSubResource("Camera") );
    m_cameraMovement.applySettings( settings.getSubResource("CameraMovement") );

    ResourceDescriptor sub = settings.getSubResource("Layer");
    if (isNotEmpty(sub.getValue())) {
        setLayer(std::stoi(sub.getValue()));
    }

    sub = settings.getSubResource("FieldOfView");
    if (isNotEmpty(sub.getValue())) {
        m_camera.setHorizontalFov(toRadians(sub.getValue()));
    }

    recalculateVerticalFov();
}

// constructor
View::View(ResourceDescriptor settings)
{
    applySettings(settings);
}

RelPixel View::fromLocation(Vector3D point) {

    m_cameraMovement.adjustForNewPoint(m_camera, point);
    
    return m_camera.fromLocation(point);
}

Inputs View::handleInputs(Inputs inputs) {

    Inputs remainingInputs;

    // adjust camera position
    Vector3D camVelocityDelta(0,0,0);

    for (Input input : inputs) {

        if (input.containsView(getName())) {

            if (input.getMotion() == InputKey::Scroll) {

                camVelocityDelta = m_cameraMovement.deltaVFromScroll(m_camera,
                            input.getScrollAmount(),
                            input.getViewIntersection(getName())
                ).plus(camVelocityDelta);
                continue;
            } 
        }

        remainingInputs.addInput(input);
    }

    // Move camera based on input
    m_cameraMovement.moveCamera(m_camera, camVelocityDelta);

    // return remaining inputs
    return remainingInputs;
}

Vector3D View::zeroPlaneIntersection(Pixel point) const {

    RelPixel relPos;

    relPos.setCol( 
            (point.getCol() - m_topLeft.getCol())
            /(m_bottomRight.getCol() - m_topLeft.getCol())
            );

    relPos.setRow( 
            (point.getRow() - m_topLeft.getRow())
            /(m_bottomRight.getRow() - m_topLeft.getRow())
            );

    return m_camera.zeroPlaneIntersection(relPos);
}

// getters and setters

void View::setName(std::string name) {
    m_name = name;
}

void View::setLayer(int layer) {
    m_layer = layer;
}

void View::setTopLeft(Pixel pixel) {
    m_topLeft = pixel;
    recalculateVerticalFov();
}

void View::setBottomRight(Pixel pixel) {
    m_bottomRight = pixel;
    recalculateVerticalFov();
}

std::string View::getName() const {
    return m_name;
}

int View::getLayer() const {
    return m_layer;
}

Pixel View::getTopLeft() const {
    return m_topLeft;
}

Pixel View::getBottomRight() const {
    return m_bottomRight;
}

void View::recalculateVerticalFov() {

    radians horFov = m_camera.getHorizontalFov();
    px width = m_bottomRight.getCol() - m_topLeft.getCol();
    px height = m_bottomRight.getRow() - m_topLeft.getRow();
    m_camera.setVerticalFov( 2*std::atan2(height*2.0*std::tan(horFov/2.0), 2.0*width) );
}


} // BattleRoom namespace
