#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "battleroom/AttributeSet.h"

#include <string>
#include <vector>
#include <map>

namespace XmlParser {


/*!
 * The XmlItem class represents a tag, its attributes, and all tags within of
 * an xml style format. There are two static member functions for constructing
 * an XmlItem, but otherwise you can only retreive the data within mentioned
 * earlier.
 * 
 * It uses the following naming convention: 
 * <Tag attribute="attribute value" > <subXmlItem /> </Tag>
 */
class XmlItem {

public:
    
    const std::string& getTag();
    const AttributeSet& getAttributeSet();

    std::vector<XmlItem> getItems();
    std::vector<XmlItem> getItems(const std::string& tag);

    /*!
     * Parses the XML file with the name given and returns an XmlItem containing
     * the xml data wrapped in a "root" tag XmlItem.
     * \param filename Name of the file to parse.
     * \return XmlItem containing XML structure within the file.
     */
    static XmlItem fromXmlFile(const std::string& filename);

    /*!
     * Parses the XML string and returns an XmlItem containing
     * the xml data wrapped in a "root" tag XmlItem.
     * \param filename Name of the file to parse.
     * \return XmlItem containing XML structure within the file.
     */
    static XmlItem fromXmlString(const std::string& xml);

private:
    
    XmlItem(const std::string& formattedString);
    AttributeSet m_attributes;
    std::vector<XmlItem> m_subitems;
    std::string m_tag;

}; // XmlItem class
} // XMLParser namespace
#endif // XMLPARSER_H
