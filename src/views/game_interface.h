#ifndef BATTLE_ROOM_GAME_INTERFACE_H
#define BATTLE_ROOM_GAME_INTERFACE_H

#include "views/view.h"
#include "views/html_menu.h"
#include "views/game_ui_element.h"
#include "views/player_select.h"

namespace BattleRoom {

    /**
     * \brief View impl for displaying the game world
     */
    class GameInterface : public View, WebMessageHandler {

    public:

        // constructor
        GameInterface(ResourceDescriptor settings, TextureManager* textureManager, int windowWidth, int windowHeight);

        // inherited
        WebMessageResponse onMessage(const std::string &message) override;

        void adjustForResize(int width, int height, int oldWidth, int oldHeight) override;

        std::vector<DrawableObject> getDrawableObjects() override;

        std::vector<DrawableMenu> getDrawableMenus() override;

        void update(seconds timestep) override;

        Inputs handleInputs(Inputs inputs) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        UniqueId m_idToTrack; ///< Tracks the given unique id

        // figure out better way to store this stuff
        // player spatial elements
        UniqueId m_playerId;
        UniqueDrawableObject m_selectedBackground;
        std::unique_ptr<PlayerSelect> m_playerSelect;

        HtmlMenu *m_htmlMenu;
        std::string url;

    }; // GameInterface class
} // BattleRoom namespace
#endif // BATTLE_ROOM_GAME_INTERFACE_H
