
#include "battle_room/common/resource_descriptor.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>

using std::string;
using std::vector;

namespace Common {

string ResourceDescriptor::getKey() {
    return m_key;
}

string ResourceDescriptor::getValue() {
    return m_value;
}

vector<ResourceDescriptor> ResourceDescriptor::getSubResources() {
    return m_subResources;
}

void ResourceDescriptor::setKey(string key) {
    m_key = key;
}

void ResourceDescriptor::setValue(string value) {
    m_value = value;
}

void ResourceDescriptor::setSubResources(vector<ResourceDescriptor> subResources) {
    m_subResources = subResources;
}

string parseOutValue(std::string line) {

    string value = "";

    // ^ beginning of line
    // \\s* All whitespace between beginning and key
    // .*:  Key and colon-space deliminator
    // (.*) The value (group 1)
    // $ end of line
    std::regex rgx_value("^\\s*.*: (.*)$");
    std::smatch sm;
    if(std::regex_search(line, sm, rgx_value)) {
         value = sm[1].str();
    }
    return value;
}


string parseOutKey(string line) {

    string key = "";

    // ^ beginning of line
    // \\s* All whitespace between beginning and key
    // (.*) The Key (group 1)
    // :.* The colon-space deliminator and the rest of the line
    std::regex rgx_key("^\\s*(.*):.*");
    std::smatch sm;
    if(std::regex_search(line, sm, rgx_key)) {
         key = sm[1].str();
    }
    return key;
}

bool isLineEmpty(string line) {

    // \\S any non-whitespace character
    std::regex rgx_char("\\S");
    std::smatch sm;
    return !std::regex_search(line, sm, rgx_char);
}

int getLevel(string line) {

    // \\t A tab character
    std::regex rgx_tab("\\t");
    string newline = std::regex_replace(line,rgx_tab,"    ");

    size_t firstNonSpace = newline.find_first_not_of(' ');
    return (firstNonSpace + 2) / 4;

}

void ResourceDescriptor::fillFromInput(vector<string> lines, unsigned& start) {
    
    if (lines.size() > start) {
        string firstLine = lines[start];

        setKey(parseOutKey(firstLine));
        setValue(parseOutValue(firstLine));
        int firstLevel = getLevel(firstLine);

        vector<ResourceDescriptor> subs;

        while (++start < lines.size()) {
            string nextLine = lines[start];

            if (!isLineEmpty(nextLine)) {
                if (getLevel(nextLine) <= firstLevel) {
                    --start;
                    break;
                } else {
                    ResourceDescriptor sub;
                    sub.fillFromInput(lines,start);
                    subs.push_back(sub);
                }
            }
        }

        setSubResources(subs);
    }
}

ResourceDescriptor::ResourceDescriptor() :
    m_key(""), m_value("")
{
}

} // Common namespace
