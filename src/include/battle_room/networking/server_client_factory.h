#ifndef SERVER_CLIENT_FACTORY_H
#define SERVER_CLIENT_FACTORY_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

/**
 * Static class for creating ServerClients
 */
class ServerClientFactory {

public:

    /**
     * \brief Create a server client from the settings
     *
     * Returns the following implementations of ServerClient based on the
     * Value of settings:
     *
     *  *Local: LocalServerClient
     *  *Host: HostServerClient
     *  *Remote: RemoteServerClient
     *
     * Any other value given will return the result of createEmptyServerClient.
     * The settings will be directly passed into the constructor of the 
     * server client.
     *
     * \param settings Settings to use to create a server client
     * \return Unique Pointer to server client instance
     */
    static UniqueServerClient createServerClient(ResourceDescriptor settings);

    /**
     * \breif Creates an empty server client - one that returns nothing
     * and updates nothing.
     * \return Unique Pointer to an empty server client instance
     */
    static UniqueServerClient createEmptyServerClient();

}; // ServerClientFactory class
} // BattleRoom namespace
#endif // SERVER_CLIENT_FACTORY_H
