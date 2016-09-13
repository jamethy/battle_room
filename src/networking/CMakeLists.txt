
cmake_minimum_required(VERSION 2.8)

add_library ( Networking
        host_server_client.cpp
        local_server_client.cpp
        remote_server_client.cpp
        server_client.cpp
        server_client_factory.cpp
        game_server.cpp
)
