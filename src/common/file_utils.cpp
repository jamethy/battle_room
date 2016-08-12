#include "battle_room/common/file_utils.h"

#include <regex>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;

namespace Common {

string getFileName(string fullFilePath) {

    string filename = fullFilePath;

    // .*\\/ file path and the last forward slash
    // (.*) the filename (group 1)
    // \\.[\\w]+ the dot and at least one word character designating the extension
    // $ end of line
    std::regex rgx_name(".*\\/(.*)\\.[\\w]+$");
    std::smatch sm;
    if(std::regex_search(fullFilePath, sm, rgx_name)) {
        filename = sm[1].str();
    }

    return filename;
}

string getFileExtension(string filename) {

    string ext = filename;

    // .*\\. file name and path including the dot before the extension
    // ([\\w]+) at least one word character designating the extension (group 1)
    // $ end of line
    std::regex rgx_ext(".*\\.([\\w]+)$");
    std::smatch sm;
    if(std::regex_search(filename, sm, rgx_ext)) {
        ext = sm[1].str();
    }

    return ext;
}

vector<string> readEntireFile(string filepath) {

    vector<string> lines;

    std::ifstream file(filepath);

    if (file.is_open()) {

        // create header line
        lines.push_back(getFileName(filepath) + ": " + getFileExtension(filepath));

        string line;
        while (getline(file,line)) {
            lines.push_back("\t" + line);
        }
    }
    else {
        std::cerr << "Unable to open file " << filepath << std::endl;
    }

    return lines;
}


} // Common namesace
