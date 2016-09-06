#include "battle_room/engine/animation/view.h"
#include <cmath>
#include <limits>

namespace BattleRoom {

const meters MAX_METERS = std::numeric_limits<double>::max();

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

    sub = settings.getSubResource("CameraFriction");
    if (isNotEmpty(sub.getValue())) {
        m_cameraFriction = std::stod(sub.getValue());
    }

    sub = settings.getSubResource("ZoomInMultiplier");
    if (isNotEmpty(sub.getValue())) {
        m_zoomInMultiplier = std::stod(sub.getValue());
    }

    sub = settings.getSubResource("ZoomOutMultiplier");
    if (isNotEmpty(sub.getValue())) {
        m_zoomOutMultiplier = std::stod(sub.getValue());
    }

    sub = settings.getSubResource("MinimumCameraZ");
    if (isNotEmpty(sub.getValue())) {
        m_minimumCameraZ = std::stod(sub.getValue());
    }
}

// constructor
View::View(ResourceDescriptor settings)
{
    applySettings(settings);
}

/**
 * \brief Gets the max x, max y, and max z of either points
 */
Vector3D getMaxEnds(Vector3D a, Vector3D b) {

    Vector3D c = a;
    if (b.x() > c.x()) { c.x() = b.x(); }
    if (b.y() > c.y()) { c.y() = b.y(); }
    if (b.z() > c.z()) { c.z() = b.z(); }
    return c;
}

/**
 * \brief Gets the min x, min y, and min z of either points
 */
Vector3D getMinEnds(Vector3D a, Vector3D b) {

    Vector3D c = a;
    if (b.x() < c.x()) { c.x() = b.x(); }
    if (b.y() < c.y()) { c.y() = b.y(); }
    if (b.z() < c.z()) { c.z() = b.z(); }
    return c;
}

RelPixel View::fromLocation(Vector3D point) {

    m_boundsMin = getMinEnds(m_boundsMin, point);
    m_boundsMax = getMaxEnds(m_boundsMax, point);

    Vector3D cameraCoord( 
            point.dot(m_camera.getRightDir()),
            point.dot(m_camera.getUpDir()),
            0
    );

    m_cameraMin = getMinEnds(m_cameraMin, cameraCoord);
    m_cameraMax = getMaxEnds(m_cameraMax, cameraCoord);

    return m_camera.fromLocation(point);
}

void View::clearCameraBounds() {
    m_boundsMin = Vector3D( MAX_METERS, MAX_METERS, MAX_METERS);
    m_boundsMax = Vector3D(-MAX_METERS,-MAX_METERS,-MAX_METERS);
    m_cameraMin = Vector3D( MAX_METERS, MAX_METERS, MAX_METERS);
    m_cameraMax = Vector3D(-MAX_METERS,-MAX_METERS,-MAX_METERS);
}

Inputs View::handleInputs(Inputs inputs) {

    Inputs remainingInputs;

    // adjust camera position
    static Vector3D camVelocity(0,0,0);

    static bool wdown = false, adown = false, sdown = false, ddown = false;
    for (Input input : inputs) {

        if (input.containsView(getName())) {

            switch(input.getKey()) {
                case InputKey::W:
                    wdown = input.getMotion() == InputKey::PressedDown;
                    break;
                case InputKey::A:
                    adown = input.getMotion() == InputKey::PressedDown;
                    break;
                case InputKey::S:
                    sdown = input.getMotion() == InputKey::PressedDown;
                    break;
                case InputKey::D:
                    ddown = input.getMotion() == InputKey::PressedDown;
                    break;
            }

            if (input.getMotion() == InputKey::Scroll) {


                if (input.getScrollAmount() < 0) {
                    // MOVE CAMERA UP
                    camVelocity = camVelocity.minus( 
                            Vector3D(0,0,m_zoomInMultiplier*input.getScrollAmount())
                            );

                    continue;
                }
                else {
                    // MOVE CAMERA TOWRAD POS
                    Vector3D zeroIntersection = input.getViewIntersection(getName());
                    camVelocity = camVelocity.plus(
                            zeroIntersection.minus(m_camera.getLocation()).getUnit()
                            .times(m_zoomOutMultiplier*input.getScrollAmount())
                            );
                    continue;
                }
            } 
        }

        remainingInputs.addInput(input);
    }

    if (wdown) {
        camVelocity = camVelocity.plus(m_camera.getUpDir().times(0.1));
    }
    if (adown) {
        camVelocity = camVelocity.minus(m_camera.getRightDir().times(0.1));
    }
    if (sdown) {
        camVelocity = camVelocity.minus(m_camera.getUpDir().times(0.1));
    }
    if (ddown) {
        camVelocity = camVelocity.plus(m_camera.getRightDir().times(0.1));
    }

    if (camVelocity.magnitude() > 0) {
        Vector3D newCamLocation = m_camera.getLocation().plus(camVelocity);

        // check known bounds
        if (newCamLocation.z() < m_minimumCameraZ) { newCamLocation.z() = m_minimumCameraZ; }
        
        if (newCamLocation.x() < m_boundsMin.x()) { newCamLocation.x() = m_boundsMin.x(); }
        else if (newCamLocation.x() > m_boundsMax.x()) { newCamLocation.x() = m_boundsMax.x(); }

        if (newCamLocation.y() < m_boundsMin.y()) { newCamLocation.y() = m_boundsMin.y(); }
        else if (newCamLocation.y() > m_boundsMax.y()) { newCamLocation.y() = m_boundsMax.y(); }


        // Check pyramid bounds

        Vector3D pyramidTop = m_boundsMax.plus(m_boundsMin).times(0.5);

        // calculate max z
        pyramidTop.z() = std::max(
                (m_cameraMax.x() - m_cameraMin.x())/(2*std::tan(m_camera.getHorizontalFov()/2.0)),
                (m_cameraMax.y() - m_cameraMin.y())/(2*std::tan(m_camera.getVerticalFov()/2.0))
        ) + m_minimumCameraZ;

        if (newCamLocation.z() > pyramidTop.z()) {
            newCamLocation = pyramidTop;
        }
        else {
            // up dir
            meters upBase = (m_cameraMax.y() - m_cameraMin.y()) / 2.0;
            meters upMax = pyramidTop.y() 
                + upBase*(pyramidTop.z() - newCamLocation.z()) 
                / (pyramidTop.z() - m_minimumCameraZ);

            if ( newCamLocation.y() - pyramidTop.y() > upMax) {
                newCamLocation.y() = upMax + pyramidTop.y();
            }
            else if ( newCamLocation.y() - pyramidTop.y() < -upMax ) {
                newCamLocation.y() = - upMax + pyramidTop.y();
            }

            // right dir
            meters rightBase = (m_cameraMax.x() - m_cameraMin.x()) / 2.0;
            meters rightMax = pyramidTop.x() 
                + rightBase*(pyramidTop.z() - newCamLocation.z()) 
                / (pyramidTop.z() - m_minimumCameraZ);

            if ( newCamLocation.x() - pyramidTop.x() > rightMax) {
                newCamLocation.x() = rightMax + pyramidTop.x();
            }
            else if ( newCamLocation.x() - pyramidTop.x() < -rightMax ) {
                newCamLocation.x() = - rightMax + pyramidTop.x();
            }
        }

        m_camera.setLocation(newCamLocation);

        // adjust velocity
        camVelocity = camVelocity.times(1 - m_cameraFriction);

        if (camVelocity.magnitude() < 0.1) {
            camVelocity = Vector3D(0,0,0);
        }
    }

    // return remaining inputs
    return remainingInputs;
}

// Reference Accessors

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
    m_boundsMin = Vector3D( 
            point.dot(m_camera.getRightDir()),
            point.dot(m_camera.getUpDir()),
            0
    );
}

void View::setBoundsMax(Vector3D point) {
    m_boundsMax = point;
    m_boundsMax = Vector3D( 
            point.dot(m_camera.getRightDir()),
            point.dot(m_camera.getUpDir()),
            0
    );
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

void View::setDrawableText(std::vector<DrawableText> texts) {
    m_texts = texts;
}

void View::setCamera(Camera camera) {
    m_camera = camera;
}


} // BattleRoom namespace
