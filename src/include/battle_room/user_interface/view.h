#ifndef VIEW_H
#define VIEW_H

#include "battle_room/common/unique_id.h"
#include "battle_room/common/pixel.h"
#include "battle_room/common/resource.h"
#include "battle_room/common/inputs.h"
#include "battle_room/common/view_interface.h"
#include "battle_room/user_interface/camera/camera.h"
#include "battle_room/user_interface/view_position.h"

namespace BattleRoom {

/**
 * \brief Area on the display window 
 * Describes a section of the display window using pixel coordinates
 * Objects to display are assigned to a view, e.g. the menu objects will be put on a menue view
 * and game objects will be put in a world view or a minimap or something
 */
    class View : public ViewInterface {

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
        RelPixel fromLocation(Vector3D point) override;

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

        void adjustForResize(int width, int height, int oldWidth, int oldHeight) override;

        // getters and setters

        UniqueId getUniqueId() const override;

        std::string getName() const;

        int getLayer() const override;

        Pixel getTopLeft() const override;

        Pixel getBottomRight() const override;

        void setName(std::string name);

        void setLayer(int layer);

        // inherited
        void applySettings(ResourceDescriptor settings);

    private:

        /**
         * \brief Utility function used to recalculate camera FOV
         */
        void recalculateVerticalFov();

        UniqueId m_uniqueId;
        std::string m_name; ///< Name and key of view
        int m_layer = 0; //< higher numbers are rendered first (therefore then covered up)
        ViewPosition m_position;
        UniqueCamera m_camera;

    }; // View class
} // BattleRoom namespace
#endif // VIEW_H
