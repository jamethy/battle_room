
#include "battle_room/common/string_utils.h"

#include <sstream>
#include <string>
#include <algorithm>

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

    string returnStr;
    std::transform(str.begin(), str.end(), returnStr.begin(), ::tolower);
    return returnStr;
}

bool keyMatch(string a, string b) {
    return toLower(a).compare(toLower(b)) == 0;
}

} // BattleRoom namespace
