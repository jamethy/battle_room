#ifndef VIEW_H
#define VIEW_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/object.h"
#include "battle_room/common/resource_descriptor.h"
#include "battle_room/engine/animation/camera.h"

namespace BattleRoom {

class View {

public:

    View(ResourceDescriptor descriptor);

    void setName(std::string name);
    void setLayer(int layer);

    void setTopLeft(Pixel pixel);
    void setBottomRight(Pixel pixel);

    void setCamera(Camera& camera);

    std::string getName();
    int getLayer();

    Pixel getTopLeft();
    Pixel getBottomRight();

    Camera& getCamera();

    void addObjects(std::vector<Object> objects);
    std::vector<Object>& getObjects();

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

    std::string m_name;
    int m_layer = 0; // the lower the number the higher the layer
    Pixel m_topLeft;
    Pixel m_bottomRight;

    Camera& m_camera;

    std::vector<Object> m_objects;

}; // View class
} // BattleRoom namespace
#endif // VIEW_H
