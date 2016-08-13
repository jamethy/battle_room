#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

namespace BattleRoom {

std::vector<std::string> split(const std::string& str, char delim);

std::string toLower(std::string str);

bool keyMatch(std::string a, std::string b);

} // BattleRoom namespace
#endif // STRING_UTILS_H
