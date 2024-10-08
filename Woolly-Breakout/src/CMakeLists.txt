cmake_minimum_required(VERSION 3.7)

project(WoollyBreakout)

message(STATUS "Starting to build project with CMake...")

if (UNIX)
	
	message(STATUS "Unix-like operating system detected")
	message(STATUS "Looking for SDL2 package")
	find_package(SDL2 REQUIRED)
	message(STATUS "SDL2 package found")
	include_directories(${SDL2_INCLUDE_DIRS})

elseif(WIN32)

	message(STATUS "Windows operating system detected")
	message(STATUS "Adding default Windows SDL2 directory for include files")
	include_directories("C:\\SDL2\\include")

	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		message(STATUS "64-bit architecture detected")
		message(STATUS "Setting SDL2 library directory as the 64-bit default directory")
		set(SDL2_LIBRARIES "C:\\SDL2\\lib\\x64\\SDL2.lib;C:\\SDL2\\lib\\x64\\SDL2main.lib")
	else()
		message(STATUS "32-bit architecture detected")
		message(STATUS "Setting SDL2 library directory as the 32-bit default directory")
		set(SDL2_LIBRARIES "C:\\SDL2\\lib\\x86\\SDL2.lib;C:\\SDL2\\lib\\x86\\SDL2main.lib")	
	endif()

endif()

message(STATUS "Adding executable from the project\'s cpp files")
add_executable(WoollyBreakout game.cpp main.cpp)

message(STATUS "Linking the project\'s header files")
target_include_directories(WoollyBreakout PUBLIC game.h)
message(STATUS "Linking SDL2 library")
target_link_libraries(WoollyBreakout ${SDL2_LIBRARIES})
