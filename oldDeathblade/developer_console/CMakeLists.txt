project(developer_console)

add_library( developer_console 
		developer_console.h developer_console.cpp
		)
target_link_libraries(developer_console base_controller ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

