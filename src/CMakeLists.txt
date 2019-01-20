cmake_minimum_required(VERSION 2.8)


set(BATTLEROOM_TARGET "battleroom")

# MAIN PROGRAM CLIENT
add_executable(battleroom
        alter_world.cpp
        alter_world.h
        animation.cpp
        animation.h
        animation_handler.cpp
        animation_handler.h
        application.cpp
        application.h
        application_message.cpp
        application_message.h
        application_message_receiver.cpp
        application_message_receiver.h
        ball.cpp
        ball.h
        battleroom.cpp
        binary_stream.cpp
        binary_stream.h
        boundary.cpp
        boundary.h
        boundary_set.cpp
        boundary_set.h
        box_boundary.cpp
        box_boundary.h
        bullet.cpp
        bullet.h
        camera.cpp
        camera.h
        camera_factory.cpp
        camera_factory.h
        circle_boundary.cpp
        circle_boundary.h
        client_connection.cpp
        client_connection.h
        client_network_handler.h
        color.cpp
        color.h
        command.cpp
        command.h
        command_receiver.cpp
        command_receiver.h
        command_type.h
        display_window.h
        drawable_menu.cpp
        drawable_menu.h
        drawable_object.cpp
        drawable_object.h
        drawable_text.cpp
        drawable_text.h
        file_utils.cpp
        file_utils.h
        frame.cpp
        frame.h
        game_interface.cpp
        game_interface.h
        game_object.cpp
        game_object.h
        game_time.cpp
        game_time.h
        input.cpp
        input.h
        input_gatherer.cpp
        input_gatherer.h
        input_keys.h
        inputs.cpp
        inputs.h
        interface_factory.cpp
        interface_factory.h
        local_updating_world.cpp
        local_updating_world.h
        local_world_updater.cpp
        local_world_updater.h
        menu.cpp
        menu.h
        menu_interface.cpp
        menu_interface.h
        message.cpp
        message.h
        message_type.h
        moving_camera.cpp
        moving_camera.h
        network_message_handler.h
        object_factory.cpp
        object_factory.h
        object_intersection.cpp
        object_intersection.h
        object_type.h
        pixel.cpp
        pixel.h
        player.cpp
        player.h
        projection1d.cpp
        projection1d.h
        pyramid_camera.cpp
        pyramid_camera.h
        quaternion.cpp
        quaternion.h
        query_world.cpp
        query_world.h
        query_world_updater.cpp
        query_world_updater.h
        rel_pixel.cpp
        rel_pixel.h
        resource.h
        resource_descriptor.cpp
        resource_descriptor.h
        sat_intersection.cpp
        sat_intersection.h
        screen_anchor.h
        sdl_client.cpp
        sdl_client.h
        sdl_display_window.cpp
        sdl_display_window.h
        sdl_drawable.cpp
        sdl_drawable.h
        sdl_drawable_image.cpp
        sdl_drawable_image.h
        sdl_drawable_text.cpp
        sdl_drawable_text.h
        sdl_font_manager.cpp
        sdl_font_manager.h
        sdl_helper_functions.cpp
        sdl_helper_functions.h
        sdl_network_helper.cpp
        sdl_network_helper.h
        sdl_server.cpp
        sdl_server.h
        sdl_texture_manager.cpp
        sdl_texture_manager.h
        server_connection.cpp
        server_connection.h
        string_utils.cpp
        string_utils.h
        unique_id.cpp
        unique_id.h
        units.cpp
        units.h
        user.cpp
        user.h
        vector2d.cpp
        vector2d.h
        vector3d.cpp
        vector3d.h
        view.cpp
        view.h
        view_interface.h
        view_position.cpp
        view_position.h
        web_app.cpp
        web_app.h
        world.cpp
        world.h
        world_updater_factory.cpp
        world_updater_factory.h
        z_max_camera.cpp
        z_max_camera.h
        web_browser_client.cpp
        web_browser_client.h
        web_renderer.cpp
        web_renderer.h
        logger.cpp
        logger.h
        texture_container.cpp
        texture_container.h
        texture_manager.h 
        html_menu.cpp 
        html_menu.h 
        input_to_cef.cpp 
        web_message_handler.h 
        )

# CEF properties
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

set(BATTLEROOM_RESOURCE_FILES
        sdl_cef_html.html
        sdl_cef_css.css
        stupid_background.png
        )

if(OS_LINUX)
    # Executable target.
#    SET_EXECUTABLE_TARGET_PROPERTIES(${BATTLEROOM_TARGET})

    # Set rpath so that libraries can be placed next to the executable.
    set_target_properties(${BATTLEROOM_TARGET} PROPERTIES INSTALL_RPATH "$ORIGIN")
    set_target_properties(${BATTLEROOM_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    set_target_properties(${BATTLEROOM_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})

    # Copy binary and resource files to the target output directory.
    COPY_FILES("${BATTLEROOM_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
    COPY_FILES("${BATTLEROOM_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
#    COPY_FILES("${BATTLEROOM_TARGET}" "${BATTLEROOM_RESOURCE_FILES}" "${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")

    # Set SUID permissions on the chrome-sandbox target.
    SET_LINUX_SUID_PERMISSIONS("${BATTLEROOM_TARGET}" "${CEF_TARGET_OUT_DIR}/chrome-sandbox")
endif()

add_custom_command(
        TARGET battleroom
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" "${CEF_TARGET_OUT_DIR}/res"
        VERBATIM
)
