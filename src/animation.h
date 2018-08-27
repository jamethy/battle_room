#ifndef ANIMATION_H
#define ANIMATION_H

#include "resource.h"
#include "frame.h"

#include <string>
#include <vector>

namespace BattleRoom {

/**
 * \brief Container of frames describing an animation
 *
 * Should only get these from AnimationHandler
 * The game engine will assign an object an animation and animation state,
 * then the graphics engine will use the state to get the frame from the animation
 */
    class Animation : public Resource {

    public:

        // constructor
        Animation(ResourceDescriptor descriptor);

        /**
         * \brief Gets the frame for the time given
         *
         * If frame not found, returns the last one
         * Should throw an exception if frame not found maybe
         *
         * \praram animationState Number of seconds into the animation
         * \return Reference to the desired frame
         */
        const Frame &getFrame(seconds animationState) const;

        seconds getLength() const;

        // getters
        
        const std::string &getName() const;

        const std::string &getImageFile() const;

        const std::string &getNextAnimation() const;

        const std::vector<Frame> &getFrames() const;

        // inherited
        void applySettings(ResourceDescriptor settings) override;

    private:

        std::string m_name; ///< Name of animation

        std::string m_imageFile; ///< Full path to image relative to resource path

        std::string m_nextAnimation; ///< Animation to go to when this one is done

        std::vector<Frame> m_frames; ///< Frames of animation (sorted by endTime)


    }; // Animation class
} // BattleRoom namespace
#endif // ANIMATION_H
