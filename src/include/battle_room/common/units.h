#ifndef UNITS_H
#define UNITS_H

#include <string>

namespace BattleRoom {

/**
 * Unit of measurement for time
 */
typedef double seconds;

/**
 * Unit of measurement in the world coordinates
 */
typedef double meters;

/**
 * \brief Unit of measurement used for rotation
 */
typedef double radians;

/**
 * \brief Parses the string for seconds
 * \param str String containing seconds to parse
 * \return Seconds value found in str
 */
seconds toSeconds(std::string str);

/**
 * \brief Utility function to parse the string for meters
 * \param str String to parse from
 * \return Value in meters found in the string
 */
meters toMeters(std::string str);

/**
 * \brief Utility function to parse the string for radians
 * \param str String to parse from
 * \return Value in radians found in the string
 */
radians toRadians(std::string str);

/**
 * \brief Converts radians to degrees
 */
double toDegrees(radians angle);

} // BattleRoom namespace
#endif // UNITS_H
