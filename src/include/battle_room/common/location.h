#ifndef LOCATION_H
#define LOCATION_H

namespace BattleRoom {

typedef double meters;

class Location {

public:

    meters& x();
    meters& y();
    meters& z();

    meters getX();
    meters getY();
    meters getZ();

    void setX(meters x);
    void setY(meters y);
    void setZ(meters z);

private:

    meters m_x = 0;
    meters m_y = 0;
    meters m_z = 0;

}; // Location class
} // BattleRoom namespace
#endif // LOCATION_H
