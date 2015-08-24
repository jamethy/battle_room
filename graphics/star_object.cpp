#include "star_object.h"
#include <iostream>
namespace GraphicsInterface
{

StarObject::StarObject()
{
}

StarObject::~StarObject()
{
}

void StarObject::startAnimation(AnimationType animation)
{
    m_animation = createAnimation(getType(), animation);
}



} // end GraphicsInterface
