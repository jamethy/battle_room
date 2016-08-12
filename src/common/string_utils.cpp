
#include "battle_room/common/string_utils.h"

#include<sstream>

using std::string;
using std::vector;

namespace Common {

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


} // Common namespace
