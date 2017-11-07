#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "battle_room/common/view_interface.h"
#include "battle_room/user_interface/spatial_element.h"

namespace BattleRoom {

    class GameInterface : public ViewInterface {

    public:

        GameInterface(ResourceDescriptor settings, UniqueId viewId);

        // inherited
        std::vector<DrawableObject> getDrawableObjects() override;

        std::vector<DrawableText> getDrawableTexts() override;

        std::vector<DrawableMenu> getDrawableMenus() override;

        void updateAnimations(seconds timestep) override;

        Inputs handleInputs(Inputs inputs) override;

        std::vector<ResourceDescriptor> getNewSettings() override;

        void applySettings(ResourceDescriptor settings) override;

    private:

        UniqueId m_idToTrack; ///< Tracks the given unique id
        UniqueId m_selectedObject; ///< Selected game object
        std::vector<SpatialElement*> m_spatialElements;

    }; // GameInterface class
} // BattleRoom namespace
#endif // GAME_INTERFACE_H
