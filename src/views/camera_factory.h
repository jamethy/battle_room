#ifndef BATTLE_ROOM_CAMERA_FACTORY_H
#define BATTLE_ROOM_CAMERA_FACTORY_H

#include "views/camera.h"

namespace BattleRoom {

/**
 * Static class for creating Cameras
 */
    class CameraFactory {

    public:

        /**
         * \brief Create a server client from the settings
         *
         * Returns the following implementations of Camera based on the
         * Value of settings:
         *
         *  *ZMax: ZMaxCamera
         *  *Pyramid: PyramidCamera
         *
         * Any other value given will return the Camera class.
         * The settings will be directly passed into the constructor of the
         * server client.
         *
         * \param settings Settings to use to create a camera
         * \return Unique Pointer to camera instance
         */
        static UniqueCamera createCamera(ResourceDescriptor settings);

        /**
         * \breif Creates a motionless camera
         * \return Unique Pointer to a Camera instance
         */
        static UniqueCamera createMotionlessCamera();

    }; // CameraFactory class
} // BattleRoom namespace
#endif // BATTLE_ROOM_CAMERA_FACTORY_H
