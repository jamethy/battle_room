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
 *
 */
    class ViewInterface : public Resource {

    public:

        // destructor
        virtual ~ViewInterface() {}

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

        virtual void update(seconds timestep) = 0;

        virtual void adjustForResize(int width, int height, int oldWidth, int oldHeight) = 0;

        virtual RelPixel fromLocation(Vector3D point) = 0;

        virtual Vector3D zeroPlaneIntersection(Pixel point) const = 0;

        virtual Pixel getTopLeft() const = 0;

        virtual Pixel getBottomRight() const = 0;

        virtual int getLayer() const = 0;

        virtual UniqueId getUniqueId() const = 0;


    }; // ViewInterface class

    typedef std::unique_ptr<ViewInterface> UniqueInterface;

} // BattleRoom namespace
#endif // VIEW_INTERFACE_H
