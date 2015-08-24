#ifndef STAR_OBJECT_H
#define STAR_OBJECT_H

#include "graphics_layer.h"

namespace GraphicsInterface
{

class StarObject : public GraphicsLayer
{

public:

    ~StarObject();
    ObjectType getType(){return Star;}
    void startAnimation(AnimationType animation);
    friend UniqueDrawableObject createObject(ObjectType obj);

private:
    StarObject();
};

} // end GraphicsInterface
#endif // STAR_OBJECT_H
