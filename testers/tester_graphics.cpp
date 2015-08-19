#include "interfaces/graphics_interface.h"

int main()
{
    GraphicsInterface::UniqueDrawableObject p1 = GraphicsInterface::createObject(GraphicsInterface::Player);
    GraphicsInterface::UniqueDrawableObject p2 = GraphicsInterface::createObject(GraphicsInterface::Player);
    GraphicsInterface::UniqueDrawableObject p3 = GraphicsInterface::createObject(GraphicsInterface::Player);
    GraphicsInterface::UniqueDrawableObject p4 = GraphicsInterface::createObject(GraphicsInterface::Player);
    GraphicsInterface::UniqueDrawableObject s1 = GraphicsInterface::createObject(GraphicsInterface::Star);
    GraphicsInterface::UniqueDrawableObject s2 = GraphicsInterface::createObject(GraphicsInterface::Star);


    delete p4.release();


    return 0;
}
