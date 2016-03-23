#include "battleroom/XmlParser.h"
#include "ParserHelperFunctions.h"

#include <string>
#include <regex>

namespace XmlParser {

////////////////////////////////////////////////////////////////////////////////
// Construction
////////////////////////////////////////////////////////////////////////////////
XmlItem::XmlItem(const std::string& formattedString) {

    std::regex rgx_tags("<(\\w*)([^<>]*)>(.*)<\\/\\1>");

    std::smatch sm;
    std::string str = formattedString;
    while(std::regex_search(str, sm, rgx_tags)) {
        m_tag = sm[1].str();
        m_attributes = parseAttributes(sm[2].str());
        if(sm.size() > 3 && sm[3].length() > 0) {
            m_subitems.push_back(XmlItem(sm[3])); 
        }
        str = sm.suffix().str();
    }
}

XmlItem XmlItem::fromXmlFile(const std::string& filename) {
    std::string xml = readEntireFile(filename);
    xml = "<root>" + filterXmlString(xml) + "</root>";
    return XmlItem(xml);
}

XmlItem XmlItem::fromXmlString(const std::string& xml) {
    return XmlItem("<root>" + filterXmlString(xml) + "</root>");
}

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////
std::string XmlItem::getTag() { 
    return m_tag;
}

std::string XmlItem::getAttribute(std::string attr) {
    auto at = m_attributes.find(attr);
    if(at == m_attributes.end()) { return ""; }
    else { return at->second; }
}

std::vector<XmlItem> XmlItem::getItems() {
    return m_subitems;
}

} // XmlParser namespace
