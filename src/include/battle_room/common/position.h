#ifndef POSITION_H
#define POSITION_H

namespace BattleRoom {

typedef double meters;

class Position {

public:

    meters getX();
    meters getY();
    void setX(meters x);
    void setY(meters y);

private:

    meters m_x;
    meters m_y;

}; // Position class
} // BattleRoom namespace
#endif // POSITION_H
