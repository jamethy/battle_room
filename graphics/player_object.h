#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "../interfaces/graphics_interface.h"

namespace GraphicsInterface
{

class PlayerObject : public DrawableObjectClass
{
private:
    PlayerObject();

public:
    ~PlayerObject();

    void setScaleX(double scale);
    void setScaleY(double scale);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void startAnimation(AnimationType animation);

    friend std::unique_ptr<DrawableObjectClass> createObject(ObjectType obj);
};

} // end GraphicsInterface
#endif // PLAYER_OBJECT_H
