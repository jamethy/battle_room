cmake_minimum_required(VERSION 2.8)


set(BATTLEROOM_TARGET "battleroom")

# MAIN PROGRAM CLIENT
add_executable(battleroom
        animation/animation.cpp
        animation/animation.h
        animation/animation_handler.cpp
        animation/animation_handler.h
        animation/boundary.cpp
        animation/boundary.h
        animation/boundary_set.cpp
        animation/boundary_set.h
        animation/box_boundary.cpp
        animation/box_boundary.h
        animation/circle_boundary.cpp
        animation/circle_boundary.h
        animation/frame.cpp
        animation/frame.h
        application/application.cpp
        application/application.h
        application/application_message.cpp
        application/application_message.h
        application/application_message_receiver.cpp
        application/application_message_receiver.h
        application/battleroom.cpp
        application/input.cpp
        application/input_gatherer.cpp
        application/input_gatherer.h
        application/input.h
        application/input_keys.h
        application/inputs.cpp
        application/inputs.h
        application/message.cpp
        application/message.h
        application/message_type.h
        common/binary_stream.cpp
        common/binary_stream.h
        common/file_utils.cpp
        common/file_utils.h
        common/logger.cpp
        common/logger.h
        common/pixel.cpp
        common/pixel.h
        common/projection1d.cpp
        common/projection1d.h
        common/quaternion.cpp
        common/quaternion.h
        common/rel_pixel.cpp
        common/rel_pixel.h
        common/resource_descriptor.cpp
        common/resource_descriptor.h
        common/resource.h
        common/sat_intersection.cpp
        common/sat_intersection.h
        common/string_utils.cpp
        common/string_utils.h
        common/unique_id.cpp
        common/unique_id.h
        common/units.cpp
        common/units.h
        common/vector2d.cpp
        common/vector2d.h
        common/vector3d.cpp
        common/vector3d.h
        display_window/display_window.h
        display_window/drawable_menu.cpp
        display_window/drawable_menu.h
        display_window/drawable_object.cpp
        display_window/drawable_object.h
        display_window/sdl_display_window.cpp
        display_window/sdl_display_window.h
        display_window/sdl_drawable.cpp
        display_window/sdl_drawable.h
        display_window/sdl_drawable_image.cpp
        display_window/sdl_drawable_image.h
        display_window/sdl_font_manager.cpp
        display_window/sdl_font_manager.h
        display_window/sdl_helper_functions.cpp
        display_window/sdl_helper_functions.h
        display_window/sdl_texture_manager.cpp
        display_window/sdl_texture_manager.h
        display_window/texture_container.cpp
        display_window/texture_container.h
        display_window/texture_manager.h
        networking/client_connection.cpp
        networking/client_connection.h
        networking/network_message_handler.h
        networking/sdl_client.cpp
        networking/sdl_client.h
        networking/sdl_network_helper.cpp
        networking/sdl_network_helper.h
        networking/sdl_server.cpp
        networking/sdl_server.h
        networking/server_connection.cpp
        networking/server_connection.h
        networking/user.cpp
        networking/user.h
        views/camera.cpp
        views/camera_factory.cpp
        views/camera_factory.h
        views/camera.h
        views/game_interface.cpp
        views/game_interface.h
        views/game_ui_element.cpp
        views/game_ui_element.h
        views/html_menu.cpp
        views/html_menu.h
        views/input_to_cef.cpp
        views/interface_factory.cpp
        views/interface_factory.h
        views/menu.cpp
        views/menu.h
        views/menu_interface.cpp
        views/menu_interface.h
        views/moving_camera.cpp
        views/moving_camera.h
        views/player_select.cpp
        views/player_select.h
        views/pyramid_camera.cpp
        views/pyramid_camera.h
        views/screen_anchor.h
        views/view.cpp
        views/view.h
        views/view_interface.h
        views/view_position.cpp
        views/view_position.h
        views/web_app.cpp
        views/web_app.h
        views/web_browser_client.cpp
        views/web_browser_client.h
        views/web_message_handler.h
        views/web_renderer.cpp
        views/web_renderer.h
        views/z_max_camera.cpp
        views/z_max_camera.h
        world/alter_world.cpp
        world/alter_world.h
        world/ball.cpp
        world/ball.h
        world/bullet.cpp
        world/bullet.h
        world/command.cpp
        world/command.h
        world/command_receiver.cpp
        world/command_receiver.h
        world/command_type.h
        world/game_object.cpp
        world/game_object.h
        world/game_time.cpp
        world/game_time.h
        world/local_updating_world.cpp
        world/local_updating_world.h
        world/local_world_updater.cpp
        world/local_world_updater.h
        world/object_factory.cpp
        world/object_factory.h
        world/object_intersection.cpp
        world/object_intersection.h
        world/object_type.h
        world/player.cpp
        world/player.h
        world/query_world.cpp
        world/query_world.h
        world/query_world_updater.cpp
        world/query_world_updater.h
        world/world.cpp
        world/world.h
        world/world_updater_factory.cpp
        world/world_updater_factory.h
        )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
target_include_directories(${BATTLEROOM_TARGET} SYSTEM PUBLIC ${CEF_INCLUDE_PATH}) # the SYSTEM ignores all the warnings

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# Determine the target output directory.
SET_CEF_TARGET_OUT_DIR()

add_dependencies(battleroom libcef_dll_wrapper)

target_link_libraries(battleroom
        libcef_dll_wrapper
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_NET_LIBRARIES}
        libcef_lib
        ${CEF_STANDARD_LIBS}
        )

if (OS_LINUX)
    # Executable target.
    #    SET_EXECUTABLE_TARGET_PROPERTIES(${BATTLEROOM_TARGET})

    # Set rpath so that libraries can be placed next to the executable.
    set_target_properties(${BATTLEROOM_TARGET} PROPERTIES INSTALL_RPATH "$ORIGIN")
    set_target_properties(${BATTLEROOM_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    set_target_properties(${BATTLEROOM_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})

    # Copy binary and resource files to the target output directory.
    COPY_FILES("${BATTLEROOM_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
    COPY_FILES("${BATTLEROOM_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")

    # Set SUID permissions on the chrome-sandbox target.
    SET_LINUX_SUID_PERMISSIONS("${BATTLEROOM_TARGET}" "${CEF_TARGET_OUT_DIR}/chrome-sandbox")
endif ()

add_custom_command(
        TARGET battleroom
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" "${CEF_TARGET_OUT_DIR}/res"
        VERBATIM
)
