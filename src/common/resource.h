#ifndef BATTLE_ROOM_RESOURCE_H
#define BATTLE_ROOM_RESOURCE_H

#include "common/resource_descriptor.h"
#include "common/string_utils.h"
#include "common/units.h"

namespace BattleRoom {

    /**
     * The start of the basis for any resource read in through a file
     * This could be an animation, map, character, etc.
     */
    class Resource {

    public:

        // destructor
        virtual ~Resource() = default;

        /**
         * \brief Fills the member variables from the settings
         * Searches the resource descriptor pair for certain Keys and
         * parses the values
         * \param settings ResourceDescriptor containing applicable settings
         */
        virtual void applySettings(ResourceDescriptor settings) = 0;

        virtual ResourceDescriptor getSettings() const = 0;

    }; // Resource class
} // BattleRoom namespace
#endif // BATTLE_ROOM_RESOURCE_H
