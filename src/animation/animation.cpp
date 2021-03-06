#include "animation/animation.h"
#include "common/logger.h"

#include <algorithm>

using std::string;
using std::vector;

namespace BattleRoom {

// apply settings

    void Animation::applySettings(ResourceDescriptor settings) {

        m_name = settings.getValue();

        ResourceDescriptor sub = settings.getSubResource("ImageFile");
        if (isNotEmpty(sub.getValue())) {
            m_imageFile = sub.getValue();
        }

        sub = settings.getSubResource("NextAnimation");
        if (isNotEmpty(sub.getValue())) {
            m_nextAnimation = sub.getValue();
        }

        vector<ResourceDescriptor> subs = settings.getSubResource("Frames").getSubResources();
        if (!subs.empty()) {

            m_frames.clear();

            for (ResourceDescriptor &rd : subs) {
                m_frames.emplace_back(rd);
            }

            std::sort(m_frames.begin(), m_frames.end(),
                      [](const Frame &a, const Frame &b) {
                          return b.getEndTime() > a.getEndTime();
                      }
            );
        }

        if (m_frames.empty()) {
            // throw exception
            Log::error("There are no frames in animation with image file ", m_imageFile, ". This will crash the game.\n");
        }
    }

    ResourceDescriptor Animation::getSettings() const {
        ResourceDescriptor rd("Animation", m_name);
        vector<ResourceDescriptor> subs;
        subs.clear();
        subs.emplace_back("ImageFile", m_imageFile);
        subs.emplace_back("NextAnimation", m_nextAnimation);
        for (const auto& frame : m_frames) {
           subs.push_back(frame.getSettings());
        }
        rd.setSubResources(subs);
        return rd;
    }

// constructor

    Animation::Animation(ResourceDescriptor descriptor) {
        applySettings(std::move(descriptor));
    }

// getters

    const string &Animation::getName() const {
        return m_name;
    }

    const string &Animation::getImageFile() const {
        return m_imageFile;
    }

    const string &Animation::getNextAnimation() const {
        return m_nextAnimation;
    }

    const vector<Frame> &Animation::getFrames() const {
        return m_frames;
    }

// other functions

    seconds Animation::getLength() const {
        return m_frames.back().getEndTime();
    }

    const Frame &Animation::getFrame(seconds animationState) const {

        for (const Frame &frame : m_frames) {
            if (animationState < frame.getEndTime()) {
                return frame;
            }
        }
        return m_frames.back();
    }

} // BattleRoom namespace
