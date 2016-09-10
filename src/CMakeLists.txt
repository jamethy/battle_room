cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_subdirectory(common)
add_subdirectory(graphics)
add_subdirectory(game)
add_subdirectory(tester_programs)

# MAIN PROGRAM CLIENT
add_executable(battleroom main.cpp )
target_link_libraries(battleroom
    Common
    Graphics
    Game
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_gfx_LIBRARY}
    ${SDL2_TTF_LIBRARY}
)

# DEDICATED SERVER
add_executable(dedicated_battleroom dedicated_server.cpp )
target_link_libraries(dedicated_battleroom
    Common
    Game
)
