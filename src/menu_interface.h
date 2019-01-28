#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#include <third_party/cef/cef_binary_3.3396.1777.g636f29b_linux64/include/internal/cef_ptr.h>
#include "view.h"
#include "menu.h"
#include "web_browser_client.h"
#include "web_renderer.h"
#include "html_menu.h"
#include "web_message_handler.h"
#include "application.h"

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

        std::vector<DrawableText> getDrawableTexts() override;

        std::vector<DrawableMenu> getDrawableMenus() override;

        void update(seconds timestep) override;

        Inputs handleInputs(Inputs inputs) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        HtmlMenu *m_htmlMenu;
        bool m_hasFocus;
        std::string url;
        Application *m_application;

    }; // MenuInterface class
} // BattleRoom namespace
#endif // MENU_INTERFACE_H

