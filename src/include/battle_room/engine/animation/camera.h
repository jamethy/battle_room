#ifndef CAMERA_H
#define CAMERA_H

#include "battle_room/common/rel_pixel.h"
#include "battle_room/common/vector3d.h"
#include "battle_room/common/quaternion.h"
#include "battle_room/common/resource.h"


namespace BattleRoom {

/**
 * \brief Class containing position of camera and calculations for its view
 */
class Camera : public Resource {

public:

    /**
     * \brief Rotates the camera over its forward-axis
     * \param theta Angle in theta to rotate
     */
    void rotateCounterClockwise(radians theta);

    // cannot do these functions until we switch graphics engine
    //void rotateUpDown(radians theta);
    //void rotateLeftRight(radians theta);

    /**
     * \brief Converts a location in space to relative position on the camera's view
     * This will be used in graphics display calculations
     * \param location Position in space to find on the screen
     * \return Position on the view in relative coordinates (0-1 will be on view)
     */
    RelPixel fromLocation(Vector3D location) const;

    /**
     * \brief From the relative position on view, calculates the direction of the 
     * ray it is pointing in
     * \param pixel Relative positionon view (0-1 is on screen)
     * \return Unit vector pointing toward the pixel
     */
    Vector3D getPixelRay(RelPixel pixel) const;

    /**
     * \brief From the relative position on view, calculates the intersection of 
     * the z = zero plane
     * This will be used to get world coordinates from input coordinates 
     *
     * \param pixel Relative position on view (0-1 is on screen)
     * \return Position in 3D space on the z=0 plane
     */
    Vector3D zeroPlaneIntersection(RelPixel pixel) const;

    // constructors

    Camera();
    Camera(ResourceDescriptor settings);

    // getters and setters

    std::string getName() const;
    Vector3D getLocation() const;
    Vector3D getUpDir() const;
    Vector3D getRightDir() const;
    Quaternion getOrientation() const;
    radians getHorizontalFov() const;
    radians getVerticalFov() const;
    void setName(std::string name);
    void setLocation(Vector3D location);
    void setOrientation(Quaternion orientation);
    void setHorizontalFov(radians angle);
    void setVerticalFov(radians angle);

    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    std::string m_name; ///< Name of camera

    Vector3D m_location; ///< Location of camera in 3D space
    Quaternion m_orientation; ///< Orientation vector in 3D space

    Vector3D m_forward; ///< Axis the camera is facing down
    Vector3D m_up; ///< Orthagonal to m_forward and straight up
    Vector3D m_right; ///< Orthagonal to m_formad 90deg to the right

    radians m_horizontalFov = 1.308333; ///< Horizontal field of view - 75 deg 
    radians m_verticalFov = 1.308333; ///< Vertical field of view - should be calculated from above

}; // Camera class
} // BattleRoom namespace
#endif // CAMERA_H
