#ifndef UNITS_H
#define UNITS_H

#include <string>
#include <limits>

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
 * \brief Degrees rotation
 */
typedef double degrees;

/**
 * \brief Mass in Kilograms
 */
typedef double kilograms;

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
 * \brief Utility function to parse the string for degrees
 * \param str String to parse from
 * \return Value in degrees found in the string
 */
degrees toDegrees(std::string str);

/**
 * \brief Utility function to parse the string for kilograms
 * @param str String to parse from
 * @return Value in kilograms found in the string
 */
kilograms toKilograms(std::string str);

/**
 * \brief Converts radians to degrees
 */
degrees toDegrees(radians angle);

/**
 * \brief Converts degrees to radians 
 */
radians toRadians(degrees angle);

const meters MAX_METERS = 99e99;
const seconds MIN_TIMESTEP = 0.0001;
const meters EPS_METERS = std::numeric_limits<double>::epsilon();

} // BattleRoom namespace
#endif // UNITS_H
