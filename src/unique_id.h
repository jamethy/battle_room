#ifndef UNIQUE_ID_H
#define UNIQUE_ID_H

#include "binary_stream.h"

#include <string>

namespace BattleRoom {

/**
 * Unique Id class for all the objects that will be passed around
 * This is needed especially for server-client relationships
 */
    class UniqueId {

    public:

        /**
         * \brief Generates an ID that is valid over the network
         * This should only be called from the server for the game world
         * \return New id that is unique across server and clients
         */
        static UniqueId generateNewNetworkId();

        /**
         * \brief Generates an ID that is only valid locally
         * This will typically be called for GUI elements
         * \return New id that is unique locally
         */
        static UniqueId generateNewLocalId();

        /**
         * \brief Generates an ID that is not valid
         * \return New id that is not valid
         */
        static UniqueId generateInvalidId();

        /**
         * \brief Generates an ID from a string
         * \return Id from string or invalid
         */
        static UniqueId fromString(std::string str);

        /**
         * Checks if the given unique id is valid
         * \return True if is valid unique id
         */
        bool isValid() const;

        /**
         * Checks if the given unique id is local
         * \return True if is local unique id
         */
        bool isLocal() const;

        /**
         * Checks if the given unique id is network
         * \return True if is network unique id
         */
        bool isNetwork() const;

        /**
         * \return String version of id
         */
        std::string toString() const;

        /**
         * \brief Overload of == operator that tests for equivelance
         * \param other UniqueId to be compared against
         * \return True if the two are equal
         */
        bool operator==(const UniqueId &other) const;

        bool operator!=(const UniqueId &other) const;

        bool operator<(const UniqueId &other) const;

        std::size_t hash() const;

        void serialize(BinaryStream& bs) const;
        static UniqueId deserialize(BinaryStream& bs);

    private:

        // private constructor
        UniqueId(int id);

        int m_id; ///< Id impl

    }; // UniqueId class
} // BattleRoom namespace

namespace std {
    template <> struct hash<BattleRoom::UniqueId> {
        size_t operator()(const BattleRoom::UniqueId& id) const {
            return id.hash();
        }
    };
}
#endif // UNIQUE_ID_H
