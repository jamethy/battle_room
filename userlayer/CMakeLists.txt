project(userlayer)



add_executable(battleroom main.cpp)

target_link_libraries(battleroom
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_gfx_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    battleroom_graphics
    battleroom_gamedata
    battleroom_utility
)
