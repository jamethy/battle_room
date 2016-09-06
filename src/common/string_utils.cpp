
#include "battle_room/common/string_utils.h"

#include <sstream>
#include <string>
#include <algorithm>
#include <regex>

using std::string;
using std::vector;

namespace BattleRoom {

vector<string> split(const string& str, char delim) {

    vector<string> items;

    std::stringstream ss(str);
    string item;
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            items.push_back(item);
        }
    }
    return items;
}

string toLower(string str) {

    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool keyMatch(string a, string b) {
    // compare returns the number of characters that differ
    return toLower(a).compare(toLower(b)) == 0;
}

bool isNotEmpty(const string& str) {

    if (str.empty()) {
        return false;
    }

    // \\S any non-whitespace character
    std::regex rgx_char("\\S");
    std::smatch sm;
    return std::regex_search(str, sm, rgx_char);
}

} // BattleRoom namespace
