#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

namespace BattleRoom {

/**
 * \brief Splits the string into sub strings by delim (copies data)
 * 
 * If str does not contain delim, the whole string is in the one 
 * element of the return vector
 *
 * \param str String to be split
 * \param delim Character to split the string by
 * \return Vector of substrings
 */
std::vector<std::string> split(const std::string& str, char delim);

/**
 * \brief Converts all the characters in str to lower case (makes a copy)
 * \param str String to be converted
 * \return All lower case version of str
 */
std::string toLower(std::string str);

/**
 * \brief Used in resource descriptor, returns match result of two keys
 *
 * (currently a string comparision that ignores case)
 *
 * \param a String to be compared to b
 * \param b String ot be compared to a
 * \return True if the two keys match
 */
bool keyMatch(std::string a, std::string b);

/**
 * \brief Checks if the string is not empty and not just whitespace
 * \param String to be examined 
 * \return True if string is not empty
 */
bool isNotEmpty(const std::string& str);

/**
 * \brief Checks if the string is empty or is just white space
 * \param String to be examined
 * \return True if string is empty
 */
bool isEmpty(const std::string& str);

/**
 * \brief Returns a copy of str with all the comments removed 
 * Comments are started with # in yml files
 * \param str String to remove comments from
 * \return Copy of str without comments
 */
std::string removeYmlComments(std::string str);

} // BattleRoom namespace
#endif // STRING_UTILS_H
