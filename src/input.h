#ifndef INPUT_H
#define INPUT_H

#include "input_keys.h"
#include "unique_id.h"
#include "vector3d.h"
#include "rel_pixel.h"

#include <unordered_map>

namespace BattleRoom {


/**
 * Container for input event. It holds the key in action, the motion of the key,
 * and the zero-plane intersection of ever view it was on
 */
    class Input {

    public:

        Input();

        /**
         * Checks the input for the view of the given name and getViewIntersection can
         * safely be used
         * \param viewName Name of the view in question
         * \return True if it does contain the view
         */
        bool containsView(UniqueId viewId);

        /**
         * Adds the view intersection point to the container
         * \param viewName Name of the view the intersection was on
         * \intersection Point in 3D space on the z = 0 plane where the event occurred
         */
        void addViewIntersection(UniqueId viewId, Vector3D intersection);
        void addViewIntersection(UniqueId viewId, RelPixel intersection);

        /**
         * Gets the Intersection of the z = 0 plane for the view
         * \param viewName Name of the view to query for
         * \return Zero-plane intersection of view or (0,0,-1) if view not hit
         */
        Vector3D getViewIntersection(UniqueId viewId);
        RelPixel getViewRelIntersection(UniqueId viewId);

        // useful matchers
        bool isKeyDown(InputKey::Key k);
        bool isKeyUp(InputKey::Key k);
        bool isModKeyDown(InputKey::Modifier mod, InputKey::Key k);
        bool isModKeyUp(InputKey::Modifier mod, InputKey::Key k);

        // getters and setters

        InputKey::Key getKey();

        InputKey::Motion getMotion();

        InputKey::Modifier getModifier();

        int getScrollAmount();

        void setKey(InputKey::Key key);

        void setMotion(InputKey::Motion motion);

        void setModifier(InputKey::Modifier modifier);

        void setScrollAmount(int amount);

    private:

        std::unordered_map<UniqueId, Vector3D> m_viewIntersections; ///< Z = 0 where mouse was
        std::unordered_map<UniqueId, RelPixel> m_viewRelIntersections; ///< Z = 0 where mouse was
        InputKey::Key m_key; ///< Key or button performing the action
        InputKey::Motion m_keyMotion; ///< Whether the key was pressed, released, or neither
        InputKey::Modifier m_modifier; ///< Which modifier key was being pressed (or none)
        int m_scrollAmount;///< Amount Scrolled - only valid when m_key == Scroll

    }; // Input class
} // BattleRoom namespace
#endif // INPUT_H
