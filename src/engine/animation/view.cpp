#include "battle_room/engine/animation/view.h"

namespace BattleRoom {

Camera emptyCamera;

View::View(ResourceDescriptor descriptor)
    : m_camera(emptyCamera)
{ 
    if (descriptor.getValue().empty()) {
        // freak out
    }
    m_name = descriptor.getValue();

    ResourceDescriptor sub = descriptor.getSubResource("Top");
    if (!sub.getKey().empty()) {
        m_topLeft.setRow(toPx(sub.getValue()));
    }

    sub = descriptor.getSubResource("Left");
    if (!sub.getKey().empty()) {
        m_topLeft.setCol(toPx(sub.getValue()));
    }

    sub = descriptor.getSubResource("Bottom");
    if (!sub.getKey().empty()) {
        m_bottomRight.setRow(toPx(sub.getValue()));
    }

    sub = descriptor.getSubResource("Right");
    if (!sub.getKey().empty()) {
        m_bottomRight.setCol(toPx(sub.getValue()));
    }
}

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

void View::setCamera(Camera& camera) {
    m_camera = camera;
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

Camera& View::getCamera() {
    return m_camera;
}

void View::addObjects(std::vector<Object> objects) {
    m_objects = objects;
}

std::vector<Object>& View::getObjects() {
    return m_objects;
}


} // BattleRoom namespace
