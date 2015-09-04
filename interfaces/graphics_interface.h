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
    Wall,
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
    virtual void setPos(const Utility::vec2d& pos, double th) = 0;
    virtual void startAnimation(AnimationType animation) = 0;
    virtual ~DrawableObjectClass();
};

typedef std::unique_ptr<DrawableObjectClass> UniqueDrawableObject;
UniqueDrawableObject createObject(ObjectType obj);


class CameraObjectClas
{
public:

    virtual void setPos(const Utility::vec2d& pos) = 0;
    virtual void setTh(const double& theta) = 0;
    virtual void setZ(const double& z) = 0;

    virtual Utility::vec2d& getPos() = 0;
    virtual double& getTh() = 0;
    virtual double& getZ() = 0;
};

class GraphicsWindowClass
{
public:

    virtual void update(const double& gameTime) = 0;

    virtual void setViewBounds(Utility::vec2d& worldMin, Utility::vec2d& worldMax) = 0;
    virtual CameraObjectClas* getCamera() = 0;

    virtual ~GraphicsWindowClass();
};


typedef std::unique_ptr<GraphicsWindowClass> UniqueGraphicsWindow;
UniqueGraphicsWindow createWindow(unsigned width, unsigned height);


} // End GraphicsInterface
#endif // GRAPHICS_INTERFACE_H
