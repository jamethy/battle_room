#ifndef GRAPHICS_INTERFACE_H
#define GRAPHICS_INTERFACE_H


#include <memory>

namespace Utility{ class vec2d; }

namespace GraphicsInterface
{

enum ObjectType
{
    Player = 0,
    Star,
    TestObject
};

enum AnimationType
{
    NoAnimation = 0,
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



class GraphicsWindowClass
{
public:
    virtual ~GraphicsWindowClass();
    virtual void setViewBounds(Utility::vec2d& worldMin, Utility::vec2d& worldMax) = 0;
    virtual void update() = 0;
};


typedef std::unique_ptr<GraphicsWindowClass> UniqueGraphicsWindow;
UniqueGraphicsWindow createWindow(unsigned width, unsigned height);


} // End GraphicsInterface
#endif // GRAPHICS_INTERFACE_H
