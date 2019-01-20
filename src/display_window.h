#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "unique_id.h"
#include "drawable_object.h"
#include "drawable_text.h"
#include "drawable_menu.h"
#include "inputs.h"
#include "resource.h"
#include "view_interface.h"
#include "texture_manager.h"

#include <vector>
#include <memory>

namespace BattleRoom {

    /**
     * \brief Window that displays graphics
     * Has views that represent portions of the screen and objects within the views
     * that are drawable
     */
    class DisplayWindow : public Resource {

    public:

        // destructor
        virtual ~DisplayWindow() {};

        /*!
         * \breif Collects window inputs to the InputGatherer
         * This should be called after every window as been drawn
         * \param views List of views associated with the window
         */
        virtual void gatherInputs(const std::vector<UniqueInterface>& views) = 0;

        /*!
         * \brief Sets the objects that need to be rendered
         * \param view used to call all the drawable getters for the view
         */
        virtual void addViewDrawables(ViewInterface* view) = 0;

        /*!
         * \brief Draws the world, UI, and then menu objects
         */
        virtual void drawScreen() = 0;

        /*!
         * \brief Switches the screen drawing buffers
         * This needs to be called in multithreaded applications - the addView* functions will
         * operate on one buffer while drawScreen operates on another.
         */
        virtual void switchBuffers() = 0;


        /**
         * Gets the unique Id of the window
         */
        virtual const UniqueId getUniqueId() const = 0;

        /**
         * Gets the name of the window
         */
        virtual std::string getName() const = 0;

        /**
         * Gets the width in pixels of the window
         */
        virtual int getWidth() const = 0;

        /**
         * Gets the height in pixels of the window
         */
        virtual int getHeight() const = 0;
        
        virtual TextureManager* getTextureManager() = 0;

    }; // DisplayWindow class

    // Window Pointer that will delete itself
    typedef std::unique_ptr<DisplayWindow> UniqueDisplayWindow;

    /*!
     * \brief Creates a display window
     * \param Resource descriptor describing the window to be created
     * \return Unique Pointer to the window that was created
     */
    UniqueDisplayWindow createDisplayWindow(ResourceDescriptor descriptor);

} // BattleRoom namespace
#endif // DISPLAY_WINDOW_H
