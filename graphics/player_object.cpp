#include "player_object.h"
#include <iostream>

namespace GraphicsInterface
{

PlayerObject::PlayerObject()
{
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::startAnimation(AnimationType animation)
{
    m_animation = createAnimation(getType(), animation);
}


} // end GraphicsInterface
