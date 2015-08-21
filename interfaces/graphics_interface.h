#ifndef GRAPHICS_INTERFACE_H
#define GRAPHICS_INTERFACE_H


#include <memory>

namespace Utility{ class vec2d; }

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
    virtual void setPos(Utility::vec2d& pos, double th) = 0;
    virtual void startAnimation(AnimationType animation) = 0;
    virtual ~DrawableObjectClass();
};

typedef std::unique_ptr<DrawableObjectClass> UniqueDrawableObject;

UniqueDrawableObject createObject(ObjectType obj);


} // End GraphicsInterface
#endif // GRAPHICS_INTERFACE_H
