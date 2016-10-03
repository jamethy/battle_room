#ifndef PROJECTION_1D_H
#define PROJECTION_1D_H

#include "battle_room/common/units.h"

namespace BattleRoom {

class Projection1D {

public:

    // constructor
    Projection1D();
    Projection1D(meters min, meters max);

    /**
     * \brief Checks if the min or max should be changed based on given point
     * \param point Point to compare min/max against
     */
    void adjustForPoint(meters point);

    /**
     * \brief Checks if the projection overlaps another
     * \param other Other proejction to compare against
     * \return False if they overlap, true otherwise
     */ 
    bool doesNotOverlap(Projection1D other);

    // getters and setters
    meters getMin();
    meters getMax();
    void setMin(meters min);
    void setMax(meters max);

private:

    meters m_min;
    meters m_max;

}; // Projection1D class
} // BattleRoom namespace
#endif // PROJECTION_1D_H
