#ifndef GRAPHICS_LAYER_H
#define GRAPHICS_LAYER_H

#include "../interfaces/graphics_interface.h"
#include "../utility/vectors.h"

namespace GraphicsInterface
{

class GraphicsLayer : public DrawableObjectClass
{

public:

    virtual Utility::vec2d& getPos();
    virtual double& getTh();

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
