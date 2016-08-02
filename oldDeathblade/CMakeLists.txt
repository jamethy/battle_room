cmake_minimum_required(VERSION 2.6)
project(project_deathblade)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_deathblade_SOURCE_DIR}/cmake")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${project_deathblade_SOURCE_DIR}/lib")
set(BIN_DIR ${project_deathblade_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
		${CMAKE_SOURCE_DIR}/
		${CMAKE_SOURCE_DIR}/include
		${SDL2_TTF_INCLUDE_DIR}
		${SDL2_gfx_INCLUDE_DIR}
		${SDL2_image_INCLUDE_DIR}
		)
link_directories(
		${CMAKE_SOURCE_DIR}/lib
		)

add_subdirectory( gameobjects )
add_subdirectory( ui_objects )
add_subdirectory( players )
add_subdirectory( developer_console )
add_subdirectory( controller_base )
add_subdirectory( controller_camera )
add_subdirectory( mainprogram )
