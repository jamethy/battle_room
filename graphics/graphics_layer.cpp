#include "graphics_layer.h"
#include "../utility/vectors.h"

namespace GraphicsInterface
{

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

void GraphicsLayer::setPos(Utility::vec2d &pos, double th)
{
    m_pos = pos;
    m_th = th;
}


void GraphicsLayer::startAnimation(AnimationType animation)
{

}


}// end GraphicsInterface
