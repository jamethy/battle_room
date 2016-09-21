cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_subdirectory(common)
add_subdirectory(graphics)
add_subdirectory(game)
add_subdirectory(user_interface)
#add_subdirectory(networking)
add_subdirectory(tester_programs)

# MAIN PROGRAM CLIENT
add_executable(battleroom main.cpp )
target_link_libraries(battleroom
    ${START_GROUP}
    Common
    Graphics
    Game
    UserInterface
    #    Networking
    ${END_GROUP}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_gfx_LIBRARY}
    ${SDL2_TTF_LIBRARY}
)

# DEDICATED SERVER
add_executable(dedicated_battleroom dedicated_server.cpp )
target_link_libraries(dedicated_battleroom
    ${START_GROUP}
    Common
    Game
    #Networking
    ${END_GROUP}
)
