#ifndef STAR_OBJECT_H
#define STAR_OBJECT_H

#include "../interfaces/graphics_interface.h"

namespace GraphicsInterface
{

class StarObject : public DrawableObjectClass
{
private:
    StarObject();

public:
    ~StarObject();

    void setX(double x);
    void setY(double y);
    void setTh(double th);
    void startAnimation(AnimationType animation);

    friend std::unique_ptr<DrawableObjectClass> createObject(ObjectType obj);
};

} // end GraphicsInterface
#endif // STAR_OBJECT_H
