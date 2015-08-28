#include "graphics_layer.h"

namespace GraphicsInterface
{

AnimationBaseClass::~AnimationBaseClass(){}

GraphicsLayer::GraphicsLayer(ObjectType type) : m_type(type)
{
    m_animation = createAnimation(getType(), NoAnimation);
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
    if(m_animation != nullptr)
        m_animation->setPosition(getPos(),getTh());
}

void GraphicsLayer::setPos(const Utility::vec2d &pos, double th)
{
    m_pos = pos;
    m_th = th;
}

AnimationBaseClass *GraphicsLayer::getAnimation(double time)
{
    if(m_animation == nullptr) return nullptr;
    m_animation->update(time);
    if(m_animation->isComplete())
    {
        m_animation = createAnimation(getType(),m_animation->after());
    }
    return m_animation.get();
}

ObjectType GraphicsLayer::getType()
{
    return m_type;
}


void GraphicsLayer::startAnimation(AnimationType animation)
{

}


}// end GraphicsInterface
