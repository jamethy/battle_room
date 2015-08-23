#ifndef GRAPHICS_LAYER_H
#define GRAPHICS_LAYER_H

#include "../interfaces/graphics_interface.h"
#include "../utility/vectors.h"

#include <chrono>

namespace GraphicsInterface
{

class AnimationClass
{
public:
    AnimationClass();
    ~AnimationClass();

private:
    std::chrono::duration<std::chrono::milliseconds> m_duration;
};

class GraphicsLayer : public DrawableObjectClass
{

public:

    virtual Utility::vec2d& getPos();
    virtual double& getTh();
    virtual ObjectType getType() = 0;

    // inherited from DrawableObjectClass
    virtual void setPos(Utility::vec2d& pos, double th);
    virtual void startAnimation(AnimationType animation);

    GraphicsLayer();
    virtual ~GraphicsLayer();

private:

    Utility::vec2d m_pos;
    double m_th = 0;
};



}// end GraphicsInterface
#endif // GRAPHICS_LAYER_H
