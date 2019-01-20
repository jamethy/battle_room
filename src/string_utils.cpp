
#include "string_utils.h"

#include <algorithm>
#include <regex>
#include <sstream>
#include <string>

using std::string;
using std::vector;

namespace BattleRoom {

    vector<string> split(const string &str, char delim) {

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
        return toLower(a) == toLower(b);
    }

    bool isNotEmpty(const string &str) {

        if (str.empty()) {
            return false;
        }

        // \\S any non-whitespace character
        std::regex rgx_char("\\S");
        std::smatch sm;
        return std::regex_search(str, sm, rgx_char);
    }

    bool isEmpty(const std::string &str) {
        return !isNotEmpty(str);
    }

    std::string removeYmlComments(std::string str) {

        std::size_t commentPos = str.find('#');
        if (commentPos != std::string::npos) {
            return str.substr(0, commentPos);
        } else {
            return str;
        }
    }

    bool isNumber(const std::string &str) {

        if (str.empty()) {
            return false;
        }

        std::regex rgx_char(R"(^\s*-?\d+\s*$)");
        std::smatch sm;
        return std::regex_search(str, sm, rgx_char);
    }

    bool startsWith(const std::string &str, const std::string &prefix) {

        if (prefix.empty()) {
            return true;
        }
        return str.find(prefix) == 0;
    }

} // BattleRoom namespace
