
#include "battle_room/common/projection1d.h"
#include "battle_room/common/vector2d.h"

namespace BattleRoom {

class SatIntersection {

    public:

        SatIntersection();

        // setters and getters
        void setIntersects(bool m_intersects);
        void setMinTranslationUnitVector(Vector2D vec);
        void setMinTranslationMagnitude(meters mag);
        bool doesIntersect();
        Vector2D getMinTranslationUnitVector();
        meters getMinTranslationMagnitude();
        Vector2D getMinTranslationVector();

    private:

        bool m_intersects; ///> true if overlapping
        Vector2D m_minTranslationUnit; ///> direction of shortest escape
        meters m_minTranslationMagnetidue; ///> amount needed to move

}; // SatIntersection class
} // BattleRoom namespace
