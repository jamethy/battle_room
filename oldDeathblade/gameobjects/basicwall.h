#ifndef BASICWALL_H
#define BASICWALL_H

#include "gameobjects/objectbase.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

/*!
 * \brief The BasicWall class is a colored polygon that can collide with other objects.
 *
 * This wall is not good. It can be any shape, however, the current function used for drawing
 * the wall is very slow and reduces frame rate considerably.
 */
class BasicWall : public ObjectBaseClass
{
public:
    BasicWall();
    ~BasicWall();

    /*!
     * \brief Creates a rectangular wall object.
     * \param x X world coordinate value for top left corner.
     * \param y Y world coordinate value for top left corner.
     * \param w Width of rectangle
     * \param h Height of rectangle
     */
    void create(double x, double y, double w, double h);

    /*!
     * \brief Uses camera to calculate wall position and draws it on renderer.
     * \param renderer Environment renderer to draw on.
     * \param camera Camera viewing the wall.
     */
    void drawon(SDL_Renderer *renderer, CameraControl* camera);

    /*!
     * \brief Sets the color of the wall to be rendered.
     * \param red Red value (0-255)
     * \param green Green value (0-255)
     * \param blue Blue value (0-255)
     * \param alpha Alpha value (0-255)
     */
    void set_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

private:
    SDL_Color color; //!< Color of wall set by set_color()
};

#endif // BASICWALL_H
