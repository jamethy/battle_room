#include <utility>


#include "resource_descriptor.h"
#include "file_utils.h"
#include "string_utils.h"

#include "include/internal/cef_string.h"
#include "include/internal/cef_types.h"
#include "include/cef_values.h"
#include "include/cef_parser.h"

#include <fstream>
#include <algorithm>
#include <regex>

using std::string;
using std::vector;

namespace BattleRoom {

    const std::string KEY_KEY = "key";
    const std::string VALUE_KEY = "value";
    const std::string SUBS_KEY = "subs";

    ResourceDescriptor::ResourceDescriptor()
            : m_key(""), m_value("") {}

    ResourceDescriptor::ResourceDescriptor(const string &key, const string &value)
            : m_key(key), m_value(value) {}

    ResourceDescriptor::ResourceDescriptor(vector<string> lines)
            : m_key(""), m_value("") {
        unsigned start = 0;
        fillFromInput(std::move(lines), start);
    }

    ResourceDescriptor toResource(const CefRefPtr<CefDictionaryValue> &dictionary) {

        ResourceDescriptor rd(dictionary->GetString(KEY_KEY), "");

        if (dictionary->HasKey(VALUE_KEY)) {
            auto valueType = dictionary->GetType(VALUE_KEY);

            std::string value;
            switch (valueType) {
                // set sub resources
                case VTYPE_BOOL:
                    value = std::to_string(dictionary->GetBool(VALUE_KEY));
                    break;
                case VTYPE_INT:
                    value = std::to_string(dictionary->GetInt(VALUE_KEY));
                    break;
                case VTYPE_DOUBLE:
                    value = std::to_string(dictionary->GetDouble(VALUE_KEY));
                    break;
                case VTYPE_STRING:
                    value = dictionary->GetString(VALUE_KEY);
                    break;

                case VTYPE_LIST:
                case VTYPE_INVALID:
                case VTYPE_NULL:
                case VTYPE_BINARY:
                case VTYPE_DICTIONARY:
                    // not allowed
                    break;
            }
            rd.setValue(value);
        }

        if (dictionary->HasKey(VALUE_KEY)) {
            vector<ResourceDescriptor> subs = {};
            auto subList = dictionary->GetList(SUBS_KEY);
            for (size_t i = 0; i < subList->GetSize(); ++i) {
                subs.push_back(toResource(subList->GetDictionary(i)));
            }
            rd.setSubResources(subs);
        }

        return rd;
    }

    ResourceDescriptor ResourceDescriptor::fromJson(const std::string &json) {
        return toResource(CefParseJSON(CefString(json), JSON_PARSER_RFC)->GetDictionary());
    }

    CefRefPtr<CefDictionaryValue> toDictionary(const ResourceDescriptor &settings) {
        auto dictionary = CefDictionaryValue::Create();

        auto key = CefValue::Create();
        key->SetString(settings.getKey());
        dictionary->SetValue(KEY_KEY, key);

        if (isNotEmpty(settings.getValue())) {
            auto value = CefValue::Create();
            value->SetString(settings.getValue());
            dictionary->SetValue(VALUE_KEY, value);
        }

        auto rdSubs = settings.getSubResources();
        if (!rdSubs.empty()) {
            auto subs = CefListValue::Create();
            subs->SetSize(rdSubs.size());
            for (size_t i = 0; i < rdSubs.size(); ++i) {
                subs->SetDictionary(i, toDictionary(rdSubs[i]));
            }
            dictionary->SetList(SUBS_KEY, subs);
        }

        return dictionary;
    }

    std::string ResourceDescriptor::toJson(const ResourceDescriptor &settings) {
        auto dictionary = toDictionary(settings);
        auto value = CefValue::Create();
        value->SetDictionary(dictionary);
        return CefWriteJSON(value, JSON_WRITER_DEFAULT).ToString();
    }

    vector<ResourceDescriptor> ResourceDescriptor::getSubResources(string filter) const {

        if (filter.empty()) {
            return m_subResources;
        }

        vector<ResourceDescriptor> returnVector;
        for (const ResourceDescriptor &descriptor : m_subResources) {
            if (filter == descriptor.getKey()) {
                returnVector.push_back(descriptor);
            }
        }

        return returnVector;
    }

    ResourceDescriptor ResourceDescriptor::getSubResource(string filter) const {

        for (const ResourceDescriptor &descriptor : m_subResources) {
            if (filter == descriptor.getKey()) {
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
    string parseOutValue(const std::string &line) {

        string value;

        // ^ beginning of line
        // \\s* All whitespace between beginning and key
        // .*:  Key and colon-space deliminator
        // (.*) The value (group 1)
        // $ end of line
        std::regex rgx_value("^\\s*.*: (.*)$");
        std::smatch sm;
        if (std::regex_search(line, sm, rgx_value)) {
            value = sm[1].str();
        }
        return value;
    }

    /**
     * \brief Utility function to get the resource's key from a line
     * \param line String with white space, key, ': ', and the value
     * \return The matched Key
     */
    string parseOutKey(const string &line) {

        string key;

        // ^ beginning of line
        // \\s* All whitespace between beginning and key
        // (.*) The Key (group 1)
        // :.* The colon-space deliminator and the rest of the line
        std::regex rgx_key("^\\s*(.*):.*");
        std::smatch sm;
        if (std::regex_search(line, sm, rgx_key)) {
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
    int getLevel(const string &line) {

        // \\t A tab character
        std::regex rgx_tab("\\t");
        string newline = std::regex_replace(line, rgx_tab, "    ");

        size_t firstNonSpace = newline.find_first_not_of(' ');

        // since zero-index, firstNonSpace = number of spaces
        return static_cast<int>((firstNonSpace + 1) / 4);

    }

    void ResourceDescriptor::fillFromInput(vector<string> lines, unsigned &start) {

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
                nextLine = removeYmlComments(nextLine);

                if (isNotEmpty(nextLine)) {

                    // if the next line is a sub of this one
                    if (getLevel(nextLine) > getLevel(firstLine)) {
                        ResourceDescriptor sub;
                        sub.fillFromInput(lines, start);
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
            for (const ResourceDescriptor &subResource : getSubResources("Resource")) {

                vector<ResourceDescriptor> newSubs = readResource(subResource.getValue()).getSubResources();
                m_subResources.insert(m_subResources.end(), newSubs.begin(), newSubs.end());
            }

        }
    }

    ResourceDescriptor ResourceDescriptor::readResource(string resourcePath) {
        if (isNotEmpty(resourcePath)) {
            return readFile(getResourcePath() + "/" + resourcePath + DESCRIPTOR_EXTENSION);
        } else {
            return ResourceDescriptor();
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

    string ResourceDescriptor::getKey() const {
        return m_key;
    }

    string ResourceDescriptor::getValue() const {
        return m_value;
    }


    void ResourceDescriptor::setKey(string key) {
        m_key = std::move(key);
    }

    void ResourceDescriptor::setValue(string value) {
        m_value = std::move(value);
    }

    void ResourceDescriptor::setSubResources(vector<ResourceDescriptor> subResources) {
        m_subResources = std::move(subResources);
    }

    void ResourceDescriptor::addSubResources(std::vector<ResourceDescriptor> subResources) {
        m_subResources.insert(m_subResources.end(), subResources.begin(), subResources.end());
    }

} // BattleRoom namespace
