#ifndef VIEW_H
#define VIEW_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/resource.h"
#include "battle_room/common/inputs.h"
#include "battle_room/graphics/camera.h"
#include "battle_room/graphics/camera_movement.h"

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
     * \brief Calculates the point in space from the point on the SCREEN
     * That's right, it does all the view calcs for you
     * \param point Pixel coordinates on the screen
     * \return Position on the z = 0 plane of point
     */
    Vector3D zeroPlaneIntersection(Pixel point) const;

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

    void setName(std::string name);
    void setLayer(int layer);
    void setTopLeft(Pixel pixel);
    void setBottomRight(Pixel pixel);

    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    /**
     * \brief Utility function used to recalculate camera FOV
     */
    void recalculateVerticalFov();

    std::string m_name; ///< Name and key of view
    int m_layer = 0; //< higher numbers are rendered first (therefore then covered up)
    Pixel m_topLeft; ///< Coordinate of top left of the view on the display window
    Pixel m_bottomRight; ///< Coordinate of bottom rightof the view on the display window

    Camera m_camera;
    CameraMovement m_cameraMovement;

}; // View class
} // BattleRoom namespace
#endif // VIEW_H
