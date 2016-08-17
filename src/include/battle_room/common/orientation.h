#ifndef ORIENTATION_H
#define ORIENTATION_H

namespace BattleRoom {

typedef double radians;

class Orientation {

public:

    radians& roll();
    radians& pitch();
    radians& yaw();

    radians getRoll();
    radians getPitch();
    radians getYaw();

    void setRoll(radians roll);
    void setPitch(radians pitch);
    void setYaw(radians yaw);

private:

    radians m_roll = 0;  // about X  
    radians m_pitch = 0; // about Y
    radians m_yaw = 0;   // about Z

}; // Orientation class
} // BattleRoom namespace
#endif // ORIENTATION_H
