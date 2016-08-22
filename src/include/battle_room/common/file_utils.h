#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <vector>
#include <string>

namespace BattleRoom {

/*!
 * Parses a file path and returns the path without the filename at the end
 */
std::string getFilePath(std::string fullFilePath);

/*!
 * Parses a file path and returns the filename without extension
 */
std::string getFileName(std::string fullFilePath);

/*!
 * Parses a file name or path and returns the extension (without the .)
 */
std::string getFileExtension(std::string filename);

/*!
 * Reads in the file and puts each line in a vector
 */
std::vector<std::string> readEntireFile(std::string filename);

} // BattleRoom namespace
#endif // FILE_UTILS_H
