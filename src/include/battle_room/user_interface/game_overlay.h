#ifndef GAME_OVERLAY_H
#define GAME_OVERLAY_H

#include "battle_room/common/view_Overlay.h"
#include "battle_room/user_Overlay/spatial_element.h"

namespace BattleRoom {

    class GameOverlay : public ViewInterface {

    public:

        GameOverlay(ResourceDescriptor settings);

        // inherited
        std::vector<DrawableObject> getDrawableObjects() override;

        std::vector<DrawableText> getDrawableTexts() override;

        Inputs handleInputs(Inputs inputs) override;

        std::vector<ResourceDescriptor> getNewSettings() override;

        void applySettings(ResourceDescriptor settings) override;

    private:

    }; // GameOverlay class
} // BattleRoom namespace
#endif // GAME_OVERLAY_H
