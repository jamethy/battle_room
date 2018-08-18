cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_subdirectory(common)
add_subdirectory(graphics)
add_subdirectory(game)
add_subdirectory(user_interface)
add_subdirectory(networking)
#add_subdirectory(tester_programs)

# MAIN PROGRAM CLIENT
add_executable(battleroom
        battleroom.cpp
        application.cpp
        )

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# Determine the target output directory.
SET_CEF_TARGET_OUT_DIR()

add_dependencies(battleroom libcef_dll_wrapper)

target_link_libraries(battleroom
        ${START_GROUP}
        Common
        Graphics
        Game
        UserInterface
        Networking
        libcef_dll_wrapper
        ${END_GROUP}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_NET_LIBRARIES}
        libcef_lib
        ${CEF_STANDARD_LIBS}
        )

set(BATTLEROOM_RESOURCE_FILES
        sdl_cef_html.html
        sdl_cef_css.css
        stupid_background.png
        )

add_custom_command(
        TARGET battleroom
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" "${CMAKE_CURRENT_BINARY_DIR}/res"
        VERBATIM
)
