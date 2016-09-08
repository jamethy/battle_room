#include "battle_room/engine/animation/view.h"

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
}

void View::setBottomRight(Pixel pixel) {
    m_bottomRight = pixel;
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


} // BattleRoom namespace
