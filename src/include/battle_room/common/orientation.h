#ifndef ORIENTATION_H
#define ORIENTATION_H

namespace BattleRoom {

typedef double radians;

class Orientation {

public:

    void setTheta(radians theta);
    radians getTheta();

private:

    radians m_theta;   

}; // Orientation class
} // BattleRoom namespace
#endif // ORIENTATION_H
