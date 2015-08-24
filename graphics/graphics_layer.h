#ifndef GRAPHICS_LAYER_H
#define GRAPHICS_LAYER_H

#include "../interfaces/graphics_interface.h"
#include "../utility/br_vectors.h"

#include <memory>

namespace GraphicsInterface
{

class AnimationBaseClass
{
public:
    virtual ~AnimationBaseClass();

    // Time update functions
    virtual void update(double time) = 0;
    virtual bool isComplete() = 0;
    virtual AnimationType after() = 0;

    // Position update functions
    virtual void setPlayerPos(Utility::vec2d& pos, double th) = 0;
    virtual Utility::vec2d& getPlayerPos() = 0;
    virtual double getPlayerTh() = 0;
};

typedef std::unique_ptr<AnimationBaseClass> UniqueAnimation;

class GraphicsLayer : public DrawableObjectClass
{

public:

    virtual Utility::vec2d& getPos();
    virtual double& getTh();
    virtual ObjectType getType() = 0;
    virtual void update();

    // inherited from DrawableObjectClass
    virtual void setPos(Utility::vec2d& pos, double th);
    virtual void startAnimation(AnimationType animation) = 0;
    virtual AnimationBaseClass* getAnimation(double time);

    GraphicsLayer();
    virtual ~GraphicsLayer();

protected:

    Utility::vec2d m_pos;
    double m_th = 0;
    UniqueAnimation m_animation;
};

UniqueAnimation createAnimation(ObjectType obj, AnimationType animation);

}// end GraphicsInterface
#endif // GRAPHICS_LAYER_H
