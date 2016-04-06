#ifndef ANIMATIONSERVICE_H
#define ANIMATIONSERVICE_H

#include "battleroom/Animation.h"

namespace Animations {

class AnimationService
{

public:
    static void addAnimation(const Animation animation);
    static const Animation& getAnimation(const std::string& name);

private:
    AnimationService();
};

} // end Animations namespace
#endif // end ANIMATIONSERVICE_H
