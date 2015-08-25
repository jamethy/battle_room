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
    virtual void setPosition(Utility::vec2d& pos, double th) = 0;
    virtual Utility::vec2d& getPosition() = 0;
    virtual double getTheta() = 0;
};

typedef std::unique_ptr<AnimationBaseClass> UniqueAnimation;

class GraphicsLayer : public DrawableObjectClass
{

public:

    Utility::vec2d& getPos();
    double& getTh();
    void update();

    // inherited from DrawableObjectClass
    void setPos(Utility::vec2d& pos, double th);
    void startAnimation(AnimationType animation);
    AnimationBaseClass* getAnimation(double time);


    ObjectType getType();
    GraphicsLayer(ObjectType type);
    virtual ~GraphicsLayer();

protected:

    Utility::vec2d m_pos;
    double m_th = 0;
    UniqueAnimation m_animation;

private:
    ObjectType m_type;
};

UniqueAnimation createAnimation(ObjectType obj, AnimationType animation);

}// end GraphicsInterface
#endif // GRAPHICS_LAYER_H
