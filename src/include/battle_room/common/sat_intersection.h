#ifndef SAT_INTERSECTION_H
#define SAT_INTERSECTION_H

#include "battle_room/common/projection1d.h"
#include "battle_room/common/vector2d.h"

namespace BattleRoom {

    /**
     * Class for storing the results for the checking for collision using the Separate Axis Theorem (SAT)
     */
    class SatIntersection {

    public:

        // constructor
        SatIntersection();

        // setters
        void setIntersects(bool m_intersects);

        void setMinTranslationUnitVector(Vector2D vec);

        void setMinTranslationMagnitude(meters mag);

        // getters
        bool doesIntersect();

        Vector2D getMinTranslationUnitVector();

        meters getMinTranslationMagnitude();

    private:

        bool m_intersects; ///> true if overlapping
        Vector2D m_minTranslationUnit; ///> direction of shortest escape
        meters m_minTranslationMagnitude; ///> amount needed to move

    }; // SatIntersection class
} // BattleRoom namespace
#endif // SAT_INTERSECTION_H
