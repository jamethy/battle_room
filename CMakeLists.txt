cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." OFF)

set (CMAKE_CXX_STANDARD 11)

project(project_deathblade)

# Specify the CEF distribution version.
set(CEF_VERSION "3.3396.1777.g636f29b")

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_deathblade_SOURCE_DIR}/cmake")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${project_deathblade_SOURCE_DIR}/lib")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${project_deathblade_SOURCE_DIR}/bin")
#set(BIN_DIR ${project_deathblade_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

if (NOT APPLE)
    set(START_GROUP "-Wl,--start-group")
    set(END_GROUP "-Wl,--end-group")
    set(LINUX_LIBS "pthread")
endif()

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)


#
# CEF configuration.
#

# Specify the CEF distribution version.
set(CEF_VERSION "3.3396.1777.g636f29b")

# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
	set(CEF_PLATFORM "macosx64")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	if(CMAKE_SIZEOF_VOID_P MATCHES 8)
		set(CEF_PLATFORM "linux64")
	else()
		set(CEF_PLATFORM "linux32")
	endif()
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	if(CMAKE_SIZEOF_VOID_P MATCHES 8)
		set(CEF_PLATFORM "windows64")
	else()
		set(CEF_PLATFORM "windows32")
	endif()
endif()

# Add this project's cmake/ directory to the module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Download and extract the CEF binary distribution (executes DownloadCEF.cmake).
include(DownloadCEF)
DownloadCEF("${CEF_PLATFORM}" "${CEF_VERSION}" "${CMAKE_SOURCE_DIR}/third_party/cef")

# Add the CEF binary distribution's cmake/ directory to the module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

# Load the CEF configuration (executes FindCEF.cmake).
find_package(CEF REQUIRED)


#
# Python configuration.
#

# Support specification of the Python executable path via the command-line.
if(DEFINED ENV{PYTHON_EXECUTABLE})
	file(TO_CMAKE_PATH "$ENV{PYTHON_EXECUTABLE}" PYTHON_EXECUTABLE)
endif()

if(NOT PYTHON_EXECUTABLE)
	unset(PYTHON_EXECUTABLE)

	# Find the python interpreter.
	find_package(PythonInterp)

	if(NOT ${PYTHONINTERP_FOUND})
		message(FATAL_ERROR "A Python installation is required. Set the "
				"PYTHON_EXECUTABLE environment variable to explicitly "
				"specify the Python executable path.")
	endif()
endif()


#
# Clang-format configuration.
#

if(OS_WINDOWS)
	set(GS_PLATFORM "win32")
	set(GS_HASHPATH "win/clang-format.exe.sha1")
elseif(OS_MACOSX)
	set(GS_PLATFORM "darwin")
	set(GS_HASHPATH "mac/clang-format.sha1")
elseif(OS_LINUX)
	set(GS_PLATFORM "linux*")
	set(GS_HASHPATH "linux64/clang-format.sha1")
endif()

message(STATUS "Downloading clang-format from Google Storage...")
execute_process(
		COMMAND "${PYTHON_EXECUTABLE}"
		"tools/download_from_google_storage.py"
		"--no_resume"
		"--platform=${GS_PLATFORM}"
		"--no_auth"
		"--bucket" "chromium-clang-format"
		"-s" "tools/${GS_HASHPATH}"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE EXECUTE_RV
)
if(NOT EXECUTE_RV STREQUAL "0")
	message(FATAL_ERROR "Execution failed with unexpected result: ${EXECUTE_RV}")
endif()


#
# Target configuration.
#

# Include the libcef_dll_wrapper target (executes libcef_dll/CMakeLists.txt).
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_net REQUIRED)

include_directories(
		${CMAKE_SOURCE_DIR}/
		${CMAKE_SOURCE_DIR}/include
		${SDL2_TTF_INCLUDE_DIR}
		${SDL2_image_INCLUDE_DIR}
        ${SDL2_NET_INCLUDE_DIRS}
		)

link_directories(
		${CMAKE_SOURCE_DIR}/lib
		)

add_subdirectory(src)

if (test)

    #enable_testing()
    #add_subdirectory(tests)

endif(test)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
