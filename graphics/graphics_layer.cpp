#include "graphics_layer.h"

namespace GraphicsInterface
{

AnimationBaseClass::~AnimationBaseClass(){}

GraphicsLayer::GraphicsLayer()
{
}

GraphicsLayer::~GraphicsLayer()
{
}


Utility::vec2d &GraphicsLayer::getPos()
{
    return m_pos;
}

double &GraphicsLayer::getTh()
{
    return m_th;
}

void GraphicsLayer::update()
{
    m_animation->setPlayerPos(getPos(),getTh());
}

void GraphicsLayer::setPos(Utility::vec2d &pos, double th)
{
    m_pos = pos;
    m_th = th;
}

AnimationBaseClass *GraphicsLayer::getAnimation(double time)
{
    m_animation->update(time);
    if(m_animation->isComplete())
    {
        m_animation = createAnimation(getType(),m_animation->after());
    }
    return m_animation.get();
}


void GraphicsLayer::startAnimation(AnimationType animation)
{

}


}// end GraphicsInterface
