#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "interfaces/graphics_interface.h"
#include "utility/br_vectors.h"

#include <memory>

namespace GameInterface
{

class ObjectBaseClass
{
public:

    virtual void updateGraphics();

    virtual ~ObjectBaseClass();
    virtual void moveTo(const Utility::WorldPos& position);
    virtual void rotateTo(const double& theta);

protected:
    ObjectBaseClass(GraphicsInterface::ObjectType type);

private:

    GraphicsInterface::UniqueDrawableObject m_graphics;

    Utility::WorldPos m_centroid;
    double m_theta;
};

} // GameInterface namespace
#endif // OBJECTBASE_H
