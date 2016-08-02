project(mainprogram)

add_executable(mainprogram main.cpp)
target_link_libraries(mainprogram
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_gfx_LIBRARY}
	base_controller
    camera_controller 
    developer_console
    gameobjects
	ui_objects
    player
)

install(TARGETS mainprogram RUNTIME DESTINATION ${BIN_DIR})

