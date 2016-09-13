#include "battle_room/common/file_utils.h"

#include <regex>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;

namespace BattleRoom {

/**
 * Static variable of the resource path
 * See setResourcePathFromExe and getResourcePath
 */
std::string m_resourcePath = "../res/";

string getFilePath(string fullFilePath) {

    string filepath = "./";

    // (.*\\/) file path and the last forward slash (group 1)
    // [^\\/]* everything but a forward stash
    // $ end of line
    std::regex rgx_path("(.*\\/)[^\\/]*$");
    std::smatch sm;
    if(std::regex_search(fullFilePath, sm, rgx_path)) {
        filepath = sm[1].str();
    }

    return filepath;
}

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

vector<string> readEntireResourceFile(string fullFilePath) {

    vector<string> lines;

    std::ifstream file(fullFilePath);

    if (file.is_open()) {

        // create header line
        lines.push_back(getFileName(fullFilePath) + ": " + getFileExtension(fullFilePath));

        string line;
        while (getline(file,line)) {
            lines.push_back("\t" + line);
        }
    }
    else {
        std::cerr << "Unable to open file " << fullFilePath << std::endl;
    }

    return lines;
}

void setResourcePathFromExe(std::string exeFilePath) {

    std::string exePath = getFilePath(exeFilePath);
    m_resourcePath = exePath + "../res/";
}

std::string getResourcePath() {
    return m_resourcePath;
}

} // BattleRoom namesace
