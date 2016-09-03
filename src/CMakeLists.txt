cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_subdirectory(common)
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tester_programs)

add_executable(battleroom main.cpp )

target_link_libraries(battleroom
    ${START_GROUP}
    Common
    Animation
    Graphics
    GameInterface
    ${END_GROUP}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_gfx_LIBRARY}
    ${SDL2_TTF_LIBRARY}
)

