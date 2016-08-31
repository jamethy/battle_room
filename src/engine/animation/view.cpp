#include "battle_room/engine/animation/view.h"

namespace BattleRoom {

void View::applySettings(ResourceDescriptor settings) {

    if (isNotEmpty(settings.getValue())) {
        setName(settings.getValue());
    }

    ResourceDescriptor sub = settings.getSubResource("TopLeft");
    if (isNotEmpty(sub.getKey())) {
        m_topLeft.applySettings(sub);
    }

    sub = settings.getSubResource("BottomRight");
    if (isNotEmpty(sub.getKey())) {
        m_bottomRight.applySettings(sub);
    }

    sub = settings.getSubResource("Layer");
    if (isNotEmpty(sub.getValue())) {
        setLayer(std::stoi(sub.getValue()));
    }

    sub = settings.getSubResource("Camera");
    if (isNotEmpty(sub.getValue())) {
        m_camera.applySettings(sub);
    }
}

// constructor
View::View(ResourceDescriptor settings)
{
    applySettings(settings);
}

// Reference Accessors

std::vector<Object>& View::getObjects() {
    return m_objects;
}

Camera& View::getCamera() {
    return m_camera;
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

std::string View::getName() {
    return m_name;
}

int View::getLayer() {
    return m_layer;
}

Pixel View::getTopLeft() {
    return m_topLeft;
}

Pixel View::getBottomRight() {
    return m_bottomRight;
}

// other functions

void View::addObjects(std::vector<Object> objects) {
    m_objects = objects;
}

void View::setCamera(Camera camera) {
    m_camera = camera;
}


} // BattleRoom namespace
