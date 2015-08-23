#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "graphics_layer.h"

namespace GraphicsInterface
{

class PlayerObject : public GraphicsLayer
{

public:

    ~PlayerObject();
    ObjectType getType(){return Player;}
    friend std::unique_ptr<DrawableObjectClass> createObject(ObjectType obj);

private:
    PlayerObject();

};

} // end GraphicsInterface
#endif // PLAYER_OBJECT_H
