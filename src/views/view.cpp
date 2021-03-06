#include "views/view.h"
#include "views/camera_factory.h"

#include <cmath>

namespace BattleRoom {

    void View::applySettings(ResourceDescriptor settings) {

        m_position.applySettings(settings.getSubResource("Position"));

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

    ResourceDescriptor View::getSettings() const {
        ResourceDescriptor rd("Interface", "Game");
        std::vector<ResourceDescriptor> subs = {};

        ResourceDescriptor sub = m_position.getSettings();
        sub.setKey("Position");
        subs.push_back(sub);

        subs.emplace_back("Layer", std::to_string(getLayer()));

        sub = m_camera->getSettings();
        sub.setKey("Camera");
        subs.push_back(sub);

        subs.emplace_back("FieldOfView", std::to_string(m_camera->getHorizontalFov()));

        rd.setSubResources(subs);
        return rd;
    }

// constructors
    View::View(ResourceDescriptor settings, int windowWidth, int windowHeight) :
        m_camera(CameraFactory::createMotionlessCamera()),
        m_uniqueId(UniqueId::generateNewLocalId()),
        m_position(ViewPosition(settings.getSubResource("Position"), windowWidth, windowHeight))
    {
        applySettings(settings);
    }

    View::View(const View &original) : 
        m_camera(UniqueCamera(original.m_camera->clone())),
        m_uniqueId(original.m_uniqueId),
        m_layer(original.m_layer),
        m_position(original.m_position)
    {}


    View &View::operator=(const View &original) {
        m_layer = original.m_layer;
        m_position = original.m_position;
        m_camera = UniqueCamera(original.m_camera->clone());
        return *this;
    }


// other functions

    RelPixel View::fromLocation(Vector3D point) {
        return m_camera->fromLocation(point);
    }

    Inputs View::handleInputs(Inputs inputs) {
        // current just passed to camera
        return m_camera->handleInputs(inputs, m_uniqueId);
    }

    Vector3D View::zeroPlaneIntersection(Pixel point) const {

        RelPixel relPos;

        relPos.setCol(
                (point.getCol() - getTopLeft().getCol())
                / (getBottomRight().getCol() - getTopLeft().getCol())
        );

        relPos.setRow(
                (point.getRow() - getTopLeft().getRow())
                / (getBottomRight().getRow() -  getTopLeft().getRow())
        );

        return m_camera->zeroPlaneIntersection(relPos);
    }

    void View::adjustForResize(int width, int height, int oldWidth, int oldHeight) {
        m_position.adjustForResize(width, height, oldWidth, oldHeight);
        recalculateVerticalFov();
    }

// getters and setters

    UniqueId View::getUniqueId() const {
        return m_uniqueId;
    }

    void View::setLayer(int layer) {
        m_layer = layer;
    }

    int View::getLayer() const {
        return m_layer;
    }

    Pixel View::getTopLeft() const {
        return m_position.getTopLeft();
    }

    Pixel View::getBottomRight() const {
        return m_position.getBottomRight();
    }

    void View::recalculateVerticalFov() {

        radians horFov = m_camera->getHorizontalFov();
        px width = getBottomRight().getCol() - getTopLeft().getCol();
        px height = getBottomRight().getRow() - getTopLeft().getRow();
        m_camera->setVerticalFov(2 * std::atan2(height * 2.0 * std::tan(horFov / 2.0), 2.0 * width));
    }

    int View::getViewWidth() {
        return m_position.getViewWidth();
    }

    int View::getViewHeight() {
        return m_position.getViewHeight();
    }

} // BattleRoom namespace
