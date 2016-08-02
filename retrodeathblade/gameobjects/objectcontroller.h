#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "controller_base/controlbaseclass.h"
#include "gameobjects/objectbase.h"
#include "players/player.h"
#include <vector>

/*!
 * \brief The ObjectController class routinely updates all objects and checks for intersections.
 */
class ObjectController {

public:
    ObjectController();
    ~ObjectController();

    /*!
     * \brief Iterates through objects and calls step_time() for each. Then checks for collisions.
     */
    void step_time();

    /*!
     * \brief Iterates through objects and calls drawon() for each.
     * \param renderer Renderer to draw the objects on.
     * \param camera Camera to be used for view angle.
     */
    void drawon(SDL_Renderer* renderer, CameraControl* camera);

    /*!
     * \brief Iterates through pairs of objects to check for collisions and collide if necessary.
     */
    void check_for_collisions();

    /*!
     * \brief Uses separate axis theorem to check if a and b are overlaping (intersecting/colliding).
     *
     * \param a An in game object.
     * \param b An in game object.
     * \param return_normal A return value of the axis with the smallest overlap distance. (collision angle)
     * \param overlap A return value of the overlap of the return_normal.
     * \return True if colliding
     */
    bool colliding(ObjectBaseClass* a, ObjectBaseClass* b, vec2d &return_normal, double &overlap);

    /*!
     * \brief Used if colliding returned true. Collides objects and creates reaction.
     * \param a An in game object
     * \param b An in game object
     * \param mtv_unit Unit vector of smallest overalp axis
     * \param mtv_mag Overlapping distance.
     */
    void bounce_objects(ObjectBaseClass* a, ObjectBaseClass* b, vec2d mtv_unit, double mtv_mag);

    /*!
     * \brief Adds object to the objects vector. Checks for duplicates.
     * \param newobject Object to be added.
     */
    void add_object(ObjectBaseClass* newobject);

private:

    /*!
     * \brief A vector of pointers to the game's objects. They are used for collision and drawing.
     */
    std::vector<ObjectBaseClass*> objects;
};


#endif // OBJECTCONTROLLER_H
