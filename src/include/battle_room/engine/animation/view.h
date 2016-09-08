#ifndef VIEW_H
#define VIEW_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/object.h"
#include "battle_room/common/drawable_text.h"
#include "battle_room/common/resource.h"
#include "battle_room/common/inputs.h"
#include "battle_room/engine/animation/camera.h"

namespace BattleRoom {

/**
 * \brief Area on the display window 
 * Describes a section of the display window using pixel coordinates
 * Objects to display are assigned to a view, e.g. the menu objects will be put on a menue view
 * and game objects will be put in a world view or a minimap or something
 */
class View : public Resource {

public:

    // constructor
    View(ResourceDescriptor settings);

    /**
     * \brief Calculates the point on the view from the point in space
     * Additionally adjusts the camera's bounds using the point
     * \param point Position in space to calculate
     * \return Location on the view of the point
     */
    RelPixel fromLocation(Vector3D point);

    /**
     * \brief Clears the bounds of the camera set by calculating locations
     */
    void clearCameraBounds();

    /**
     * \brief Handles any inputs for the view and returns remaining
     * Mainly used for camera controls
     * \param inptus Collection of inputs to look through
     * \return Remaining inputs that weren't used
     */
    Inputs handleInputs(Inputs inputs);

    // getters and setters

    std::string getName() const;
    int getLayer() const;
    Pixel getTopLeft() const;
    Pixel getBottomRight() const;
    const Camera& getCamera() const;
    Vector3D getBoundsMin() const;
    Vector3D getBoundsMax() const;

    void setName(std::string name);
    void setLayer(int layer);
    void setTopLeft(Pixel pixel);
    void setBottomRight(Pixel pixel);
    void setCamera(Camera camera);
    void setBoundsMin(Vector3D point);
    void setBoundsMax(Vector3D point);

    // inherited
    void applySettings(ResourceDescriptor settings);

    //TODO figure out how to get rid of this
    View& operator=(const View& other) {
        m_name = other.m_name;
        m_topLeft = other.m_topLeft;
        m_bottomRight = other.m_bottomRight;
        m_camera = other.m_camera;
        return *this;
    }

private:

    std::string m_name; ///< Name and key of view
    int m_layer = 0; //< higher numbers are rendered first (therefore then covered up)
    Pixel m_topLeft; ///< Coordinate of top left of the view on the display window
    Pixel m_bottomRight; ///< Coordinate of bottom rightof the view on the display window
    double m_cameraFriction = 0.5; ///< Friction of camera motion
    double m_zoomInMultiplier = 1.0; ///< Multiplier of zooming input
    double m_zoomOutMultiplier = 1.0; ///< Multiplier of zooming input
    meters m_minimumCameraZ = 10;

    Camera m_camera;

    Vector3D m_boundsMin; ///< Minimum x and y of point in view
    Vector3D m_boundsMax; ///< Maximum x and y of point in view
    Vector3D m_cameraMin; ///< Minimum point in view in camera coordinates
    Vector3D m_cameraMax; ///< Maximum point in view in camera coordinates

}; // View class
} // BattleRoom namespace
#endif // VIEW_H
