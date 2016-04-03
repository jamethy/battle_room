#include "ParserHelperFunctions.h"

#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <algorithm>
#include <regex>

// TODO Add some error checking to these functions, for example, 
// ending a comment too early
// mispelling a tag
namespace XmlParser {

std::string readEntireFile(const std::string& filename) {

    std::ifstream t(filename);
    if(!t.is_open()) return "";

    std::string str;

    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

    return str;
}

std::string removeAllLineEndings(std::string str) {
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}

std::string removeAllComments(const std::string& str) {
    std::regex comments ("<!--[^>]*-->");
    return std::regex_replace(str, comments, "");
}

std::string expandAllSelfenclosed(const std::string& str) {

    std::regex comments ("<(\\w*)([^>]*)/>");
    return std::regex_replace(str, comments, "<$1$2></$1>");
}

std::unordered_map<std::string,std::string> parseAttributes( 
                                  const std::string& attribute_set) {

    std::unordered_map<std::string,std::string> attrs_map;

    std::regex rgx_attr("\\s*(\\w+)=\"([^\\\"]+)\"");
    std::smatch sm;
    std::string str = attribute_set;
    while(std::regex_search(str, sm, rgx_attr)) {
        attrs_map.insert(std::pair<std::string,std::string>(sm[1].str(),sm[2].str()));
        str = sm.suffix().str();
    }
    return attrs_map;
}

std::string filterXmlString(const std::string& str) {
    std::string s = str;
    s = removeAllLineEndings(s);
    s = removeAllComments(s);
    s = expandAllSelfenclosed(s);
    return s;
}

} // XmlParser namespace

