
set( BUILD_GTEST ON )
unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_definitions(-DTEST_FILES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/res")

add_subdirectory( lib/googletest )

include_directories(
        ${gtest_SOURCE_DIR}/include 
        ${gtest_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src/include
        )

add_subdirectory( common )
