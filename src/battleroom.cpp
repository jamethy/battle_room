#include "resource_descriptor.h"
#include "file_utils.h"
#include "application.h"
#include "Logger.h"

#include <fstream>

using namespace BattleRoom;

std::string getStartupScriptFromArgs(int argc, char **argv);

int main(int argc, char **argv) {

    Log::debug("Hello World!");

    // if called for web rendering process, return code
    auto renderProcessCode = Application::initializeWeb(argc, argv);
    if (renderProcessCode >= 0) {
        Log::info("Received positive web response: ", renderProcessCode);
        return renderProcessCode;
    }

    // Read in the startup script settings file
    std::string settings_file = getStartupScriptFromArgs(argc, argv);
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

    Log::info("Instantiating the application");
    Application application(rd);
    application.runApplicationLoop();

    return 0;

} // end main

bool fileExists(const std::string &filename) {
    std::ifstream inFile;
    inFile.open(filename);

    if (!inFile.is_open()) {
        return false;
    } else {
        inFile.close();
        return true;
    }
}

std::string getStartupScriptFromArgs(int argc, char **argv) {

    setResourcePathFromExe(argv[0]);
    std::string startupScript = getResourcePath() + "/startup" + DESCRIPTOR_EXTENSION;

    if (argc > 1) {
        std::string arg = argv[1];

        // try with no additions
        if (fileExists(arg)) {
            startupScript = arg;
        } else {

            // check if file extension is there, and then in res
            if (isEmpty(getFileExtension(arg))) {
                arg += DESCRIPTOR_EXTENSION;
            }

            if (fileExists(arg)) {
                startupScript = arg;
            } else {
                arg = getResourcePath() + "/" + arg;
                if (fileExists(arg)) {
                    startupScript = arg;
                }
            }
        }

        Log::info("Startup script: " + startupScript);
        setResourcePathFromStartupScript(startupScript);
    }

    return startupScript;
}
