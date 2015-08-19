#ifndef GRAPHICS_INTERFACE_H
#define GRAPHICS_INTERFACE_H

#include <memory>

namespace GraphicsInterface
{

enum ObjectType
{
    Player,
    Star
};

enum AnimationType
{
    TestAnimation
};


class DrawableObjectClass
{
public:
    virtual void setScaleX(double scale) = 0;
    virtual void setScaleY(double scale) = 0;
    virtual void setX(double x) = 0;
    virtual void setY(double y) = 0;
    virtual void setZ(double z) = 0;
    virtual void startAnimation(AnimationType animation) = 0;
    virtual ~DrawableObjectClass();
};

typedef std::unique_ptr<DrawableObjectClass> UniqueDrawableObject;

UniqueDrawableObject createObject(ObjectType obj);


} // End GraphicsInterface
#endif // GRAPHICS_INTERFACE_H
