#include "battle_room/graphics/view.h"
#include "battle_room/graphics/camera_factory.h"

#include <cmath>

namespace BattleRoom {

    void View::applySettings(ResourceDescriptor settings) {

        if (isNotEmpty(settings.getValue())) {
            setName(settings.getValue());
        }

        m_topLeft.applySettings(settings.getSubResource("TopLeft"));
        m_bottomRight.applySettings(settings.getSubResource("BottomRight"));

        ResourceDescriptor sub = settings.getSubResource("Layer");
        if (isNotEmpty(sub.getValue())) {
            setLayer(std::stoi(sub.getValue()));
        }

        sub = settings.getSubResource("Camera");
        if (isNotEmpty(sub.getValue())) {
            m_camera = CameraFactory::createCamera(sub);
        } else if (isNotEmpty(sub.getKey())) {
            m_camera->applySettings(sub);
        }

        sub = settings.getSubResource("FieldOfView");
        if (isNotEmpty(sub.getValue())) {
            m_camera->setHorizontalFov(toRadians(sub.getValue()));
        }

        recalculateVerticalFov();
    }

// constructors
    View::View(ResourceDescriptor settings)
            : m_camera(CameraFactory::createMotionlessCamera()) {
        applySettings(settings);
    }

    View::View(const View &original)
            : m_name(original.m_name),
              m_layer(original.m_layer),
              m_topLeft(original.m_topLeft),
              m_bottomRight(original.m_bottomRight),
              m_camera(UniqueCamera(original.m_camera->clone())) {}


    View &View::operator=(const View &original) {
        m_name = original.m_name;
        m_layer = original.m_layer;
        m_topLeft = original.m_topLeft;
        m_bottomRight = original.m_bottomRight;
        m_camera = UniqueCamera(original.m_camera->clone());
        return *this;
    }


// other functions

    RelPixel View::fromLocation(Vector3D point) {
        return m_camera->fromLocation(point);
    }

    Inputs View::handleInputs(Inputs inputs) {
        // current just passed to camera
        return m_camera->handleInputs(inputs, getName());
    }

    Vector3D View::zeroPlaneIntersection(Pixel point) const {

        RelPixel relPos;

        relPos.setCol(
                (point.getCol() - m_topLeft.getCol())
                / (m_bottomRight.getCol() - m_topLeft.getCol())
        );

        relPos.setRow(
                (point.getRow() - m_topLeft.getRow())
                / (m_bottomRight.getRow() - m_topLeft.getRow())
        );

        return m_camera->zeroPlaneIntersection(relPos);
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

        radians horFov = m_camera->getHorizontalFov();
        px width = m_bottomRight.getCol() - m_topLeft.getCol();
        px height = m_bottomRight.getRow() - m_topLeft.getRow();
        m_camera->setVerticalFov(2 * std::atan2(height * 2.0 * std::tan(horFov / 2.0), 2.0 * width));
    }

} // BattleRoom namespace
