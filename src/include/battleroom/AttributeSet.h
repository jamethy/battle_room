#ifndef ATTRIBUTESET_H
#define ATTRIBUTESET_H

#include "Points.h"

#include <unordered_map>

namespace XmlParser {

class AttributeSet {

private:

    std::unordered_map<std::string,std::string> m_attributes;

public:

    AttributeSet();
    AttributeSet(const std::string& attributes);

    std::string getString( const std::string& attribute, 
                           const std::string defaultValue) const;

    int getInt( const std::string& attribute, 
                const int defaultValue) const;

    double getDouble( const std::string& attribute, 
                      const double defaultValue) const;

    IntPoint getIntPoint( const std::string& attribute,
                          const IntPoint defaultValue) const;

    DoublePoint getDoublePoint( const std::string& attribute,
                                const DoublePoint defaultValue) const;
};

} // XmlParser namespace
#endif // ATTRIBUTESET_H
