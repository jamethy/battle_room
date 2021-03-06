#include "views/camera_factory.h"
#include "views/z_max_camera.h"
#include "views/pyramid_camera.h"

namespace BattleRoom {

    UniqueCamera CameraFactory::createCamera(ResourceDescriptor settings) {

        if (keyMatch("ZMax", settings.getValue())) {
            return UniqueCamera(new ZMaxCamera(settings));
        } else if (keyMatch("Pyramid", settings.getValue())) {
            return UniqueCamera(new PyramidCamera(settings));
        } else {
            return UniqueCamera(new Camera(settings));
        }
    }

    UniqueCamera CameraFactory::createMotionlessCamera() {
        return UniqueCamera(new Camera());
    }

} // BattleRoom namespace
