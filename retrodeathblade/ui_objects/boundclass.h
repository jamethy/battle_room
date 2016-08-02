#ifndef BOUNDCLASS_H
#define BOUNDCLASS_H

#include "gameobjects/objectbase.h"
#include "controller_camera/cameracontrol.h"

/*!
 * \brief The BoundClass class is a very early implementation of how a player controls a bounce.
 */
class BoundClass
{
public:
    BoundClass();
    ~BoundClass();

    double xclick; //!< X game coordinate of where the click started
    double yclick; //!< Y game coordinate of where the click started
    double xdrag; //!< Width in pixels of where the click will end
    double ydrag; //!< Height in pixels of where the click will end

    //ObjectBaseClass* bound_object;

    /*!
     * \brief Draws the bounding GUI on the window
     * \param renderer Renderer to draw the GUI on
     * \param camera Tells where to draw it
     */
    void drawon(SDL_Renderer* renderer, CameraControl* camera);

    /*!
     * \brief If the user has entered something.
     */
    bool enabled;


};

#endif // BOUNDCLASS_H
