project( base_controller )

add_library( base_controller
	tempsettings.h tempsettings.cpp
	controlbaseclass.h controlbaseclass.cpp
	gameenums.h
)

target_link_libraries( base_controller ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

