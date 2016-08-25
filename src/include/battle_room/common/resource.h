#ifndef RESOURCE_H
#define RESOURCE_H

#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

/**
 * The start of the basis for any resource read in through a file
 * This could be an animation, map, character, etc.
 */
class Resource {

public:

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
