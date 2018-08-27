#ifndef PROJECTION_1D_H
#define PROJECTION_1D_H

#include "units.h"

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
         * \brief Checks if the min or max should be changed based on other adjustment
         * \param projection Projection to compare min/max against
         */
        void adjustForProjection(Projection1D projection);

        /**
         * \brief Checks if the projection overlaps another
         * \param other Other proejction to compare against
         * \return False if they overlap, true otherwise
         */
        bool doesNotOverlap(const Projection1D &other) const;

        /**
         * @brief Calculates the amount of overlap between projections
         * Not valid if doesNotOverlap returns true
         * @param other Overlapping projection
         * @return Amount of overlap
         */
        meters getOverlap(const Projection1D &other) const;

        // getters and setters
        meters getMin() const;

        meters getMax() const;

        meters getMid() const;

        void setMin(meters min);

        void setMax(meters max);

    private:

        meters m_min;
        meters m_max;

    }; // Projection1D class
} // BattleRoom namespace
#endif // PROJECTION_1D_H
