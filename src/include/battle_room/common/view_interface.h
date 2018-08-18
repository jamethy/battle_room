#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H

#include "battle_room/common/resource.h"
#include "battle_room/common/unique_id.h"
#include "battle_room/common/inputs.h"
#include "battle_room/common/drawable_object.h"
#include "battle_room/common/drawable_text.h"
#include "battle_room/common/drawable_menu.h"

#include <memory>
#include <vector>

namespace BattleRoom {

    /**
     * \brief Interface for views
     *
     * Views are portions of the screen that can produce drawables
     * and handle inputs
     *
     * Views should be created using the InterfaceFactory
     *
     */
    class ViewInterface : public Resource {

    public:

        // destructor
        ~ViewInterface() override = default;

        /**
         * \brief Handle inputs and return any remaining
         * \param inputs Collection of inputs from the display window
         * \return Remaining inputs that were not used here
         */
        virtual Inputs handleInputs(Inputs inputs) = 0;

        /**
         * \brief Gets a list of objects that are drawable (probably on associated view)
         * \return List of objects
         */
        virtual std::vector<DrawableObject> getDrawableObjects() = 0;

        /**
         * \brief Gets a list of drawable texts (probably on associated view)
         * \return List of texts
         */
        virtual std::vector<DrawableText> getDrawableTexts() = 0;

        /**
         * \brief Gets a list of drawable menus (probably on associated view)
         * \return List of menus
         */
        virtual std::vector<DrawableMenu> getDrawableMenus() = 0;

        /**
         * \brief Update the view's animations, camera, etc
         * \param timestep real world seconds that have passed since last update
         */
        virtual void update(seconds timestep) = 0;

        /**
         * \brief Adjust the view for resizing of the window
         * \param width New width in pixels of the window
         * \param height New height in pixels of the window
         * \param oldWidth Old width in pixels of the window
         * \param oldHeight Old height in pixels of the window
         */
        virtual void adjustForResize(int width, int height, int oldWidth, int oldHeight) = 0;

        /**
         * \brief From the point in the 3D game world, calculate the relative pixel of the view
         * \return where on the view in relative pixel coordinates is point displayed
         */
        virtual RelPixel fromLocation(Vector3D point) = 0;

        /**
         * \brief From the absolute screen pixel point, calculate the ray from the view's camera 
         * to the point on the screen and return the intersection of that ray with the z = 0 plane
         * \return where in the game world the pixel intersects and z = 0
         */
        virtual Vector3D zeroPlaneIntersection(Pixel point) const = 0;

        /**
         * \return most top-left row and column of the view
         */
        virtual Pixel getTopLeft() const = 0;

        /**
         * \return most bottom-right row and column of the view
         */
        virtual Pixel getBottomRight() const = 0;

        /**
         * \brief higher numbers are rendered first (therefore then covered up)
         * \return the z-layer of the view, used for rendering and input handling
         */
        virtual int getLayer() const = 0;

        /**
         * \return the unique identifier of the view
         */
        virtual UniqueId getUniqueId() const = 0;

    }; // ViewInterface class

    typedef std::unique_ptr<ViewInterface> UniqueInterface;

} // BattleRoom namespace
#endif // VIEW_INTERFACE_H
