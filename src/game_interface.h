#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "view.h"

namespace BattleRoom {

    /**
     * \brief View impl for displaying the game world
     */
    class GameInterface : public View {

        public:

            // constructor
            GameInterface(ResourceDescriptor settings, int windowWidth, int windowHeight);

            // inherited
            std::vector<DrawableObject> getDrawableObjects() override;
            std::vector<DrawableText> getDrawableTexts() override;
            std::vector<DrawableMenu> getDrawableMenus() override;
            void update(seconds timestep) override;
            Inputs handleInputs(Inputs inputs) override;
            void applySettings(ResourceDescriptor settings) override;

        private:

            UniqueId m_idToTrack; ///< Tracks the given unique id

            // figure out better way to store this stuff
            // player spatial elements
            UniqueId m_playerId;
            UniqueDrawableObject m_selectedBackground;
            UniqueDrawableObject m_chargingGun;
            UniqueDrawableObject m_chargingJump;


    }; // GameInterface class
} // BattleRoom namespace
#endif // GAME_INTERFACE_H
