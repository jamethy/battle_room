#ifndef BATTLE_ROOM_MENU_INTERFACE_H
#define BATTLE_ROOM_MENU_INTERFACE_H

#include "views/view.h"
#include "views/menu.h"
#include "views/web_browser_client.h"
#include "views/web_renderer.h"
#include "views/html_menu.h"
#include "views/web_message_handler.h"
#include "application/application.h"

namespace BattleRoom {

    /**
     * \brief View impl for displaying a menu
     */
    class MenuInterface : public View, WebMessageHandler {

    public:

        // constructor
        MenuInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth, int windowHeight,
                      Application *application);

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

        HtmlMenu *m_htmlMenu;
        std::string url;
        Application *m_application;

    }; // MenuInterface class
} // BattleRoom namespace
#endif // BATTLE_ROOM_MENU_INTERFACE_H

