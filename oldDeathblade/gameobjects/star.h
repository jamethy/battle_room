#ifndef STAR_H
#define STAR_H

#include "gameobjects/objectbase.h"
#include "SDL.h"

/*!
 * \brief The Star class represents a star object!
 */
class Star : public ObjectBaseClass
{
public:
    Star();
    ~Star();

    /*!
     * \brief Sets the texture of the star to star_texture and sets its game coordinate size.
     * \param star_texture Teture to use for star
     * \param width in game coordinates
     * \param height in game coordinates
     */
    void setTexture(SDL_Texture* star_texture, double width, double height);

    // inherited functions
    void step_time();
    bool isMobile(){return true;}
    void drawon(SDL_Renderer* renderer, CameraControl* camera);

private:

    SDL_Texture* star_texture; //!< Texture of the star to animate. Set with setTexture.
    double texturewidth; //!< Width of star object in game coordinates
    double textureheight; //!< Height of star object in game coordinates
};

#endif // STAR_H
