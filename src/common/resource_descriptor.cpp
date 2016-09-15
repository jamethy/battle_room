
#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"
#include "battle_room/common/string_utils.h"

#include <fstream>
#include <algorithm>
#include <regex>

using std::string;
using std::vector;

namespace BattleRoom {

ResourceDescriptor::ResourceDescriptor() 
    : m_key(""), m_value("")
{ }

ResourceDescriptor::ResourceDescriptor(vector<string> lines) 
    : m_key(""), m_value("")
{
    unsigned start = 0;
    fillFromInput(lines, start);
}

vector<ResourceDescriptor> ResourceDescriptor::getSubResources(string filter) {

    if (filter.empty()) {
        return m_subResources;
    }

    vector<ResourceDescriptor> returnVector;
    for (ResourceDescriptor& descriptor : m_subResources) {
        if (filter.compare(descriptor.getKey()) == 0) {
            returnVector.push_back(descriptor);
        }
    }

    return returnVector;
}

ResourceDescriptor ResourceDescriptor::getSubResource(string filter) {
    
    for (ResourceDescriptor& descriptor : m_subResources) {
        if (filter.compare(descriptor.getKey()) == 0) {
            return descriptor;
        }
    }
    // if none matched, return empty descriptor
    return ResourceDescriptor();
}

/**
 * \brief Utility function to get the resource's value from a line
 * \param line String with white space, key, ': ', and the value
 * \return The matched Value
 */ 
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

/**
 * \brief Utility function to get the resource's key from a line
 * \param line String with white space, key, ': ', and the value
 * \return The matched Key
 */
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

/**
 * \brief Utility function to count the number of tabs before the key
 *
 * A tab is considered 4 spaces (and 4 spaces a tab) and the result is rounded half
 *
 * \param line containing key-value pair
 * \return Number of tabs before the key
 */
int getLevel(string line) {

    // \\t A tab character
    std::regex rgx_tab("\\t");
    string newline = std::regex_replace(line,rgx_tab,"    ");

    size_t firstNonSpace = newline.find_first_not_of(' ');

    // since zero-index, firstNonSpace = number of spaces
    return (firstNonSpace + 1) / 4;

}

void ResourceDescriptor::fillFromInput(vector<string> lines, unsigned& start) {
    
    // if we haven't reached end of file
    if (lines.size() > start) {

        string firstLine = lines[start];

        // set this resource descriptor's values
        setKey(parseOutKey(firstLine));
        setValue(parseOutValue(firstLine));

        // then get it's subs
        vector<ResourceDescriptor> subs;

        while (++start < lines.size()) {
            string nextLine = lines[start];

            if (isNotEmpty(nextLine)) {

                // if the next line is a sub of this one
                if (getLevel(nextLine) > getLevel(firstLine)) {
                    ResourceDescriptor sub;
                    sub.fillFromInput(lines,start);
                    subs.push_back(sub);
                } 
                // else, undo iteration and let the upper layer handle the next line
                else {
                    --start;
                    break;
                }
            }
        }

        setSubResources(subs);

        // check for Resource sub
        for (ResourceDescriptor subResource : getSubResources("Resource")) {

            if (isNotEmpty(subResource.getValue())) {

                string file = getResourcePath() + "/" 
                    + subResource.getValue() + DESCRIPTOR_EXTENSION;

                vector<ResourceDescriptor> newSubs = readFile(file).getSubResources();
                m_subResources.insert(m_subResources.end(), newSubs.begin(), newSubs.end());
            }
        }
        
    }
}

ResourceDescriptor ResourceDescriptor::readFile(string filePath) {


    vector<string> resourceFile = readEntireResourceFile(filePath);

    unsigned start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(resourceFile, start);

    return descriptor;
}


// setters and getters

string ResourceDescriptor::getKey() {
    return m_key;
}

string ResourceDescriptor::getValue() {
    return m_value;
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

} // BattleRoom namespace
