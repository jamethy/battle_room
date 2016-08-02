project( camera_controller )

add_library( camera_controller
	cameracontrol.h cameracontrol.cpp
)
target_link_libraries(camera_controller ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

