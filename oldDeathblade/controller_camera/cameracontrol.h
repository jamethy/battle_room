#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include "controller_base/gameenums.h"
#include "controller_base/tempsettings.h"
#include "controller_base/controlbaseclass.h"

#include <iostream>
#include <cmath>
#include <vector>
#include "SDL.h"


/*!
 * \brief The CameraControl class moves the camera according to mouse and mouse wheel inputs.
 *
 * This class functions on the concept that the camera is an object in the game's 3D space. The
 * x,y dimension are the plane of the game with (0,0) being the top left corner, and the z dimension
 * is 'above' the game.
 */
class CameraControl : public ControlBaseClass {

public:

    /*!
     * \brief Constructor for class
     * \param gamesettings The pointer to the main game controller. (sort of a parent object)
     */
    CameraControl(TempSettings *gamesettings);
    ~CameraControl();

    /*!
     * \brief Based on input (usually from the mouse wheel), changes the z-value of the camera.
     *
     * \param input Negative values zoom out and positive values zoom in.
     * \param mouse_x Used to zoom in where mouse is pointing. In pixels.
     * \param mouse_y Used to zoom in where mouse is pointing. In pixels.
     */
    void adjust_zoom(int input, double mouse_x, double mouse_y);
    /*!
     * \brief Moves the camera based on mouse movement if mouse_control==true
     * \param relative_x X movement of the mouse in pixels
     * \param relative_y Y movement of the mouse in pixels
     */
    void mousecontrol_move(int mouse_x, int mouse_y, int relative_x, int relative_y, bool rotating);

    /*!
     * \brief Moves the camera based on input from wasd/arrows/mouse(not yet). Speed is pan_speed setting.
     * \param xdirection -1 for left, +1 for right
     */
    void pan_leftright(int xdirection);

    /*!
     * \brief Moves the camera based on input from wasd/arrows/mouse(not yet). Speed is pan_speed setting.
     * \param xdirection -1 for up, +1 for down
     */
    void pan_updown(int ydirection);

    /*!
     * \brief Rotates the camera clockwise on input from ctrl+mouse movement.
     * \param delta_theta Change in camera angle to rotate.
     */
    void rotate_view(double delta_theta);

    /*!
     * \brief Given a position in space, calculates the pixel destination.
     * \param x X position in space
     * \param y Y position in space
     * \param w Width of object in space
     * \param h Height of object in space
     * \param zplane Which plane the object is on.
     * \return Destination rectangle for rendering.
     */
    SDL_Rect calculate_display_destination ( double x,
                                             double y,
                                             double w,
                                             double h,
                                             db::ZPlane zplane);
    /*!
     * \brief Uses the pointers to an objects x,y as camx,y inputs.
     * \param objectx Pointer to the x value of the object to be tracked.
     * \param objecty Pointer to the y value of the object to be tracked.
     */
    void track_object(double* objectx, double* objecty);
    /*!
     * \brief Sets tracking_on to false and the x,y pointers to null.
     */
    void stop_tracking();

    // These functions calculate space coordinates from pixel dimensions
    double xfrompixel(int pixelX, int pixelY, db::ZPlane z);
    double yfrompixel(int pixelX, int pixelY, db::ZPlane z);
    double wfrompixel(int pixelW, db::ZPlane z);
    double hfrompixel(int pixelH, db::ZPlane z);

    // These functions calculate pixel coordinates from space dimensions
    int pixelfromx(double x, double y, db::ZPlane z);
    int pixelfromy(double x, double y, db::ZPlane z);
    int pixelfromw(double w, db::ZPlane z);
    int pixelfromh(double h, db::ZPlane z);

    // inherited functions
    void update_settings();
    std::string parse_arguments(std::vector<std::string> args);

    // Basic private member manipulation
    void mousecontrol_on(){ mouse_control = true;}
    void mousecontrol_off(){ mouse_control = false;}
    bool mouse_controlling(){ return mouse_control;}
    bool is_tracking(){ return tracking_on;}

    double camyaw; //!< Yaw of of the camera (rotate view) (in radians)

protected:

    /*!
     * \brief Checks camx and camy versus the max and min of each.
     *
     * This calculation is based on max/min_x/y of course, but also
     * tanfovx/y and x/y_sidebuffer.
     */
    void checkcamxy();

    /*!
     * \brief Based on the rotation of the camera, this function calculates the min/max 'x/y' the camera can see.
     *
     * x and y are in quotation because it is really the x/y projected onto the camera's horizontal/vertical axes.
     */
    void calculate_camera_bounds();

    /*!
     * \brief Pointer to the object dealing with basic game settings such as resolution.
     */
    TempSettings *game_settings;

    double camx; //!< X world coordinate of camera
    double camy; //!< Y world coordinate of camera
    double camz; //!< Z world coordinate of camera

    double* xtracking; //!< X world coordinate to track
    double* ytracking; //!< Y world coordinate to track

    double maxview_w; //!< Max horizontal view distance of the camera
    double minview_w; //!< Min horizontal view distance of the camera
    double maxview_h; //!< Max vertical view distance of the camera
    double minview_h; //!< Min vertical view distance of the camera
    double max_z; //!< Max Z world coordinate of camera
    double min_z; //!< Min Z world coordinate of camera

    bool mouse_control; //!< Toggle for when mouse is in control
    bool tracking_on; //!< Toggle for camx/y tracks x/ytracking pointers

    // player prefernce settings
    double zoomin_speed;    //!< Sensitivity of mousewheel up: zoom in
    double zoomout_speed;   //!< Sensitivity of mousewheel down: zoom out
    double zoom_friction;   //!< How quickly the camera loses momentum
    bool momentum_on;       //!< Turn momentum off
    double sidebuffer;    //!< Viewable distance of map
    double pan_speed;       //!< Speed of panning with wasd/arrows/mouse

    double fieldofview_w; //!< Field of view in the x direction (in radians)
    double fieldofview_h; //!< Field of view in the y direction (in radians)

    // Other variables used internally.
    std::vector<double> planeZs;        //!< The depths associated with each ZPlane
    std::vector<double> pixelratio;     //!< Pixels per world unit, for each ZPlane
    double dx,dy,dz; //!< Speed of camera movement used for momentum.

    //convenient
    double tanfov_w; //!< tangent of fieldofview_w/2
    double tanfov_h; //!> tangent of fieldofview_h/2
};

#endif // CAMERACONTROL_H
