#ifndef RESOURCE_H
#define RESOURCE_H

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/string_utils.h"

namespace BattleRoom {

/**
 * \brief Unit of measurement used for rotation
 */
typedef double radians;

/**
 * Unit of measurement in the world coordinates
 */
typedef double meters;


/**
 * The start of the basis for any resource read in through a file
 * This could be an animation, map, character, etc.
 */
class Resource {

public:

    // destructor
    virtual ~Resource(){}

    /**
     * \brief Fills the member variables from the settings
     * Searches the resource descriptor pair for certain Keys and 
     * parses the values
     * \param settings ResourceDescriptor containing applicable settings
     */
    virtual void applySettings(ResourceDescriptor settings) = 0;

}; // Resource class
} // BattleRoom namespace
#endif // RESOURCE_H
