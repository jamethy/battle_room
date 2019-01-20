#ifndef BATTLE_ROOM_FILE_UTILS_H
#define BATTLE_ROOM_FILE_UTILS_H

#include <string>
#include <vector>

namespace BattleRoom {

    /*!
     * \brief Parses a file path and returns the path without the filename at the end
     *
     * Returns "./" if path is not found in input
     *
     * \param fullFilePath String containing path and possibly a filename at the end
     * \return New string of just the path including the last forward slash
     */
    std::string getFilePath(const std::string &fullFilePath);

    /*!
     * \brief Parses a file path and returns the filename without extension
     *
     * Returns an empty string if filename not found in argument
     *
     * \param fullFilePath String containing path and a filename at the end
     * \return New string of just the filename (without the . or extension at end)
     */
    std::string getFileName(const std::string &fullFilePath);

    /*!
     * \breif Parses a file name or path and returns the extension (without the .)
     *
     * Returns an empty string if extension not found
     *
     * \param filename Filename or full file path that has a . and extension at the end
     * \return New string of just the extension
     */
    std::string getFileExtension(const std::string &filename);

    /*!
     * \breif Reads in the resource file and puts each line in a vector
     *
     * Additionally adds a line at the top that contains "<filename>: <extension>" and
     * adds a tab before every line thereafter. This is so the ResourceDescriptor class
     * can parse it correctly
     *
     * Returns an empty vector if file not found
     *
     * \param fullFilePath String containing the full file path and name
     * \return A string of each line in the file as a string
     */
    std::vector<std::string> readEntireResourceFile(const std::string &fullFilePath);

    /*!
     * \brief Sets the resource path from the path of the executable
     * \param Relative path to the executable
     */
    void setResourcePathFromExe(const std::string &exePath);

    /*!
     * \brief Sets the resource path from the path of the startup script
     * \param Relative path to the startup script
     */
    void setResourcePathFromStartupScript(const std::string &startupPath);

    /*!
     * \brief Gets the resource path
     * \param Absolute resource path
     */
    std::string getResourcePath();

} // BattleRoom namespace
#endif // BATTLE_ROOM_FILE_UTILS_H
