#ifndef VIEW_H
#define VIEW_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/resource.h"
#include "battle_room/common/inputs.h"
#include "battle_room/graphics/camera.h"
#include "battle_room/graphics/view_position.h"

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
        View(ResourceDescriptor settings, int windowWidth, int windowHeight);

        View(const View &original);

        View &operator=(const View &original);

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

        void adjustForResize(int width, int height, int oldWidth, int oldHeight);

        // getters and setters

        std::string getName() const;

        int getLayer() const;

        Pixel getTopLeft() const;

        Pixel getBottomRight() const;

        void setName(std::string name);

        void setLayer(int layer);

        // inherited
        void applySettings(ResourceDescriptor settings);

    private:

        /**
         * \brief Utility function used to recalculate camera FOV
         */
        void recalculateVerticalFov();

        std::string m_name; ///< Name and key of view
        int m_layer = 0; //< higher numbers are rendered first (therefore then covered up)
        ViewPosition m_position;
        UniqueCamera m_camera;

    }; // View class
} // BattleRoom namespace
#endif // VIEW_H
