#ifndef FRAME_H
#define FRAME_H

#include "battle_room/common/resource.h"
#include "battle_room/common/pixel.h"
#include "battle_room/common/boundary_set.h"

namespace BattleRoom {

/**
 * \brief Frame in an animation. Each frame cuts out a portion of
 * the image file and has an end time to mark its point in the 
 * animation.
 *
 * These objects is also constant and should never change
 */
    class Frame : public Resource {

    public:

        // Constructors
        Frame(ResourceDescriptor descriptor);

        /**
         * \brief Calculates and returns the width from topLeft/botRight
         * \return Width of object in space
         */
        meters getWidth() const;

        /**
         * \brief Calculates and returns the height from topLeft/botRight
         * \return Height of object in space
         */
        meters getHeight() const;

        // getters

        seconds getEndTime() const;

        const Pixel &getTopLeft() const;

        const Pixel &getBottomRight() const;

        double getScale() const;

        std::string getFlip() const;

        const BoundarySet &getBoundarySet() const;

        // inherited
        void applySettings(ResourceDescriptor settings) override;

    private:

        seconds m_endTime; ///< Time to move to next frame

        Pixel m_topLeft; ///< Position of the top-left of the frame in the image
        Pixel m_bottomRight; ///< Position of the bottom-rightof the frame in the image

        double m_scale; // meters per pixel, amount to stretch image
        std::string m_flip; // horizontal, veritcal, both, none

        BoundarySet m_boundarySet;

    }; // Frame class
} // BattleRoom namespace
#endif // FRAME_H
