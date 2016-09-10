#ifndef GET_RESOURCE_PATH_H
#define GET_RESOURCE_PATH_H

#include <string>

namespace BattleRoom {

/*
 * \brief Function that currently relies on SDL that gets the path to
 * the resource directory
 * \TODO find a better place for this
 * \return Full path to the resource directory
 */
std::string getResourcePath();


}// BattleRoom namespace
#endif // GET_RESOURCE_PATH_H
