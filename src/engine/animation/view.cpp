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

void View::adjustBoundsFor(Vector3D point) {

    if (point.x() < m_boundsMin.x()) {
        m_boundsMin.x() = point.x();
    } else if (point.x() > m_boundsMax.x()) {
        m_boundsMax.x() = point.x();
    }

    if (point.y() < m_boundsMin.y()) {
        m_boundsMin.y() = point.y();
    } else if (point.y() > m_boundsMax.y()) {
        m_boundsMax.y() = point.y();
    }

    if (point.z() < m_boundsMin.z()) {
        m_boundsMin.z() = point.z();
    } else if (point.z() > m_boundsMax.z()) {
        m_boundsMax.z() = point.z();
    }

}

Inputs View::handleInputs(Inputs inputs) {

    static Vector3D camVelocity(0,0,0);

    Inputs remainingInputs;

    Vector3D cameraDelta(0,0,0);
    for (Input input : inputs) {

        if (input.containsView(getName())) {

            if (input.getMotion() == InputKey::Scroll) {

                if (input.getScrollAmount() < 0) {
                    // MOVE CAMERA UP
                    cameraDelta = cameraDelta.plus( 
                            Vector3D(0,0,-input.getScrollAmount())
                    );

                    continue;
                }
                else {
                    // MOVE CAMERA TOWRAD POS
                    Vector3D zeroIntersection = input.getViewIntersection(getName());
                    cameraDelta = cameraDelta.plus(
                            zeroIntersection.minus(m_camera.getLocation()).getUnit()
                            .times(input.getScrollAmount()));
                    continue;
                }
            } 
        }

        remainingInputs.addInput(input);
    }

    m_camera.setLocation( m_camera.getLocation().plus(cameraDelta) );
    return remainingInputs;
}

// Reference Accessors

std::vector<Object> View::getObjects() const {
    return m_objects;
}

std::vector<DrawableText> View::getTexts() const {
    return m_texts;
}

Camera& View::camera() {
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

void View::setBoundsMin(Vector3D point) {
    m_boundsMin = point;
}

void View::setBoundsMax(Vector3D point) {
    m_boundsMax = point;
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

const Camera& View::getCamera() const {
    return m_camera;
}

Vector3D View::getBoundsMin() const {
    return m_boundsMin;
}

Vector3D View::getBoundsMax() const {
    return m_boundsMax;
}

// other functions

void View::setObjects(std::vector<Object> objects) {
    m_objects = objects;
}

void View::setDrawableText(std::vector<DrawableText> texts) {
    m_texts = texts;
}

void View::setCamera(Camera camera) {
    m_camera = camera;
}


} // BattleRoom namespace
