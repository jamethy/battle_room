#include "common/file_utils.h"
#include "common/logger.h"

#include <regex>
#include <fstream>
#include <zconf.h>

using std::string;
using std::vector;

namespace BattleRoom {

    /**
     * Static variable of the resource path
     * See setResourcePathFromExe and getResourcePath
     */
    string m_resourcePath = "../res/";

    string getFilePath(const string &fullFilePath) {

        string filepath = "./";

        // (.*\\/) file path and the last forward slash (group 1)
        // [^\\/]* everything but a forward stash
        // $ end of line
        std::regex rgx_path("(.*\\/)[^\\/]*$");
        std::smatch sm;
        if (std::regex_search(fullFilePath, sm, rgx_path)) {
            filepath = sm[1].str();
        }

        return filepath;
    }

    string getFileName(const string &fullFilePath) {

        string filename;

        // .*\\/ file path and the last forward slash
        // (.*) the filename (group 1)
        // \\.[\\w]+ the dot and at least one word character designating the extension
        // $ end of line
        std::regex rgx_name(R"(.*\/(.*)\.[\w]+$)");
        std::smatch sm;
        if (std::regex_search(fullFilePath, sm, rgx_name)) {
            filename = sm[1].str();
        }

        return filename;
    }

    string getFileExtension(const string &filename) {


        // .*\\. file name and path including the dot before the extension
        // ([\\w]+) at least one word character designating the extension (group 1)
        // $ end of line
        std::regex rgx_ext(".*\\.([\\w]+)$");
        std::smatch sm;
        string ext;
        if (std::regex_search(filename, sm, rgx_ext)) {
            ext = sm[1].str();
        }

        return ext;
    }

    vector<string> readEntireResourceFile(const string &fullFilePath) {

        vector<string> lines;

        std::ifstream file(fullFilePath);

        if (file.is_open()) {

            // create header line
            lines.push_back(getFileName(fullFilePath) + ":");
            lines.push_back("  Type: " + getFileExtension(fullFilePath));

            string line;
            while (getline(file, line)) {
                lines.push_back("  " + line);
            }
        } else {
            Log::error("Unable to open file " + fullFilePath);
        }

        return lines;
    }

    void setResourcePathFromExe(const string &exeFilePath) {

        string exePath = getFilePath(exeFilePath);

        char resolved_path[PATH_MAX];
        realpath((exePath + "res/").c_str(), resolved_path);
        m_resourcePath = std::string(resolved_path) + "/";
    }

    void setResourcePathFromStartupScript(const string &startupFilePath) {

        string startupPath = getFilePath(startupFilePath);

        char resolved_path[PATH_MAX];
        realpath(startupPath.c_str(), resolved_path);
        m_resourcePath = std::string(resolved_path) + "/";
    }

    string getResourcePath() {
        return m_resourcePath;
    }
} // BattleRoom namesace
