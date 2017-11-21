#ifndef COLLISION_REACTIONS_H
#define COLLISION_REACTIONS_H

#include "battle_room/common/vector2d.h"
#include "battle_room/game/game_object.h"

namespace BattleRoom {

    class ObjectIntersection {

    public:
        /**
         * Constructor
         * @param objA
         * @param objB
         * @param sat
         */
        ObjectIntersection(GameObject *objA, GameObject *objB, SatIntersection sat);

        static std::vector<ObjectIntersection> getIntersections(const std::vector<GameObject*>& objects);

        /**
         *
         */
        void reactToCollision();

        GameObject* getObjectA();
        GameObject* getObjectB();


    private:

        GameObject *m_objectA;
        GameObject *m_objectB;
        Vector2D m_minTransUnit;
        meters m_minTransMag;

    }; // ObjectIntersection class
} // BattleRoom namespace
#endif // COLLISION_REACTIONS_H
