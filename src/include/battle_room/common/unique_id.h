#ifndef UNIQUE_ID_H
#define UNIQUE_ID_H

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
     * Checks if the given unique id is valid
     * \return True if is valid unique id
     */
    bool isValid();

    /**
     * \brief Overload of == operator that tests for equivelance
     * \param other UniqueId to be compared against
     * \return True if the two are equal
     */
    bool operator==(const UniqueId& other) const;
    bool operator!=(const UniqueId& other) const;

private:

    // private constructor
    UniqueId(long long id);

    long long m_id; ///< Id impl

}; // UniqueId class
} // BattleRoom namespace
#endif // UNIQUE_ID_H
