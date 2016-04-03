#include "battleroom/AttributeSet.h"
#include "ParserHelperFunctions.h"

#include <regex>
#include <cstdlib>
#include <stdlib.h>

namespace XmlParser {

////////////////////////////////////////////////////////////////////////////////
// Construction
////////////////////////////////////////////////////////////////////////////////

AttributeSet::AttributeSet() { }

AttributeSet::AttributeSet(const std::string& attributes) {
    m_attributes = parseAttributes(attributes);
}

////////////////////////////////////////////////////////////////////////////////
// Helper functions 
////////////////////////////////////////////////////////////////////////////////
bool isInt(const std::string& str) {
    std::regex rgx_int("^\\d+$");
    return std::regex_match(str,rgx_int);
}

bool isDouble(const std::string& str) {
    std::regex rgx_float("^\\d+\\.?\\d*$");
    return std::regex_match(str,rgx_float);
}

bool isIntPoint(const std::string& str) {
    std::regex rgx_point("^\\(\\d+,\\d+\\)$");
    return std::regex_match(str,rgx_point);
}

bool isDoublePoint(const std::string& str) {
    std::regex rgx_point("^\\(\\d+\\.?\\d*,\\d+\\.?\\d*\\)$");
    return std::regex_match(str,rgx_point);
}

std::string getPointFirst(const std::string& str) {
    std::regex rgx_point("^\\((\\d+\\.?\\d*),(\\d+\\.?\\d*)\\)$");
    std::smatch sm;
    if(std::regex_search(str,sm,rgx_point)) {
        return sm[1];
    } else {
        return "";
    }
}

std::string getPointSecond(const std::string& str) {
    std::regex rgx_point("^\\((\\d+\\.?\\d*),(\\d+\\.?\\d*)\\)$");
    std::smatch sm;
    if(std::regex_search(str,sm,rgx_point)) {
        return sm[2];
    } else {
        return "";
    }
}

////////////////////////////////////////////////////////////////////////////////
// Getters 
////////////////////////////////////////////////////////////////////////////////
std::string AttributeSet::getString( const std::string& attribute,
                                     const std::string defaultValue ) const {
    auto attr = m_attributes.find(attribute);
    return attr == m_attributes.end() ? defaultValue : attr->second;
}

int AttributeSet::getInt( const std::string& attribute,
                          const int defaultValue ) const {

    auto attr = m_attributes.find(attribute);

    if(attr != m_attributes.end() && isInt(attr->second)) {
        return atoi(attr->second.c_str());
    } else {
        return defaultValue;
    }
}

double AttributeSet::getDouble( const std::string& attribute,
                                const double defaultValue ) const {

    auto attr = m_attributes.find(attribute);

    if(attr != m_attributes.end() && isDouble(attr->second)) {
        return atof(attr->second.c_str());
    } else {
        return defaultValue;
    }
}

IntPoint AttributeSet::getIntPoint( const std::string& attribute,
                                    const IntPoint defaultValue ) const {

    auto attr = m_attributes.find(attribute);

    if(attr != m_attributes.end() && isIntPoint(attr->second)) {
        int a = atoi(getPointFirst(attr->second).c_str());
        int b = atoi(getPointSecond(attr->second).c_str());
        return IntPoint(a,b);
    } else {
        return defaultValue;
    }
}

DoublePoint AttributeSet::getDoublePoint( const std::string& attribute,
                                          const DoublePoint defaultValue ) const {

    auto attr = m_attributes.find(attribute);

    if(attr != m_attributes.end() && isDoublePoint(attr->second)) {
        double a = atof(getPointFirst(attr->second).c_str());
        double b = atof(getPointSecond(attr->second).c_str());
        return DoublePoint(a,b);
    } else {
        return defaultValue;
    }
}

} // XmlParser namespace
