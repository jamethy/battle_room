#ifndef TEXTUREWALL_H
#define TEXTUREWALL_H

#include "gameobjects/objectbase.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

/*!
 * \brief The TextureWall class is a simple wall stretching a texture. More efficient than BasicWall.
 */
class TextureWall : public ObjectBaseClass
{
public:
    TextureWall();
    ~TextureWall();

    /*!
     * \brief Sets the wall's texture and size in game coordinates.
     * \param wall_texture Texture to use for wall. This will be stretched to size.
     * \param width in game coordinates.
     * \param height in game coordinates.
     */
    void setTexture(SDL_Texture* wall_texture, double width, double height);

    // Inherited functions.
    void drawon(SDL_Renderer *renderer, CameraControl* camera);

private:

    SDL_Texture* wall_texture; //!< Texture to use for wall. Set with setTexture().
    double width; //!< Width of wall in game coordinates
    double height; //!< Height of wall in game coordinates


};

#endif // TEXTUREWALL_H
