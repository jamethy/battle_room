#ifndef VIEW_H
#define VIEW_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/object.h"
#include "battle_room/common/resource_descriptor.h"
#include "battle_room/engine/animation/camera.h"

namespace BattleRoom {

/**
 * \brief Area on the display window 
 * Describes a section of the display window using pixel coordinates
 * Objects to display are assigned to a view, e.g. the menu objects will be put on a menue view
 * and game objects will be put in a world view or a minimap or something
 */
class View {

public:

    // constructor
    View(ResourceDescriptor settings);

    /**
     * \brief Fills the member varibles using settings
     * \param settings Resource descriptor containing information about the view
     */
    void applySettings(ResourceDescriptor settings);

    // Reference Accessors
    Camera& getCamera();
    std::vector<Object>& getObjects();


    // getters and setters

    void setName(std::string name);
    void setLayer(int layer);
    void setTopLeft(Pixel pixel);
    void setBottomRight(Pixel pixel);

    std::string getName();
    int getLayer();
    Pixel getTopLeft();
    Pixel getBottomRight();


    /**
     * \brief Currently just sets the object vector
     */
    void addObjects(std::vector<Object> objects);

    /**
     * Sets the reference to the camera (does not copy)
     * So this view will then track the given camera
     */
    void setCamera(Camera& camera);

    //TODO figure out how to get rid of this
    View& operator=(const View& other) {
        m_name = other.m_name;
        m_topLeft = other.m_topLeft;
        m_bottomRight = other.m_bottomRight;
        m_camera = other.m_camera;
        m_objects = other.m_objects;
        return *this;
    }

private:

    std::string m_name; ///< Name and key of view
    int m_layer = 0; //< higher numbers are rendered first (therefore then covered up)
    Pixel m_topLeft; ///< Coordinate of top left of the view on the display window
    Pixel m_bottomRight; ///< Coordinate of bottom rightof the view on the display window

    Camera& m_camera; ///< Reference to camera that should be tracked

    std::vector<Object> m_objects; ///< Objects to draw on view

}; // View class
} // BattleRoom namespace
#endif // VIEW_H
