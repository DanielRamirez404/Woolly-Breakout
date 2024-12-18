cmake_minimum_required(VERSION 3.7)

project(WoollyBreakout)

message(STATUS "Starting to build project with CMake...")

if (UNIX)

	message(STATUS "Unix-like operating system detected")
	message(STATUS "Looking for SDL2 package")
	find_package(SDL2 REQUIRED)
	message(STATUS "SDL2 package found")
	message(STATUS "Looking for SDL2_image package")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
	find_package(SDL2_image REQUIRED)
	message(STATUS "SDL2_image package found")
	include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
	
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

message(STATUS "Creating executable from the project\'s source code")

file(GLOB src
	"main.cpp"
	"constants/*"
	"game/*"
	"game/map/*"
	"game/entities/*"
)

add_executable(WoollyBreakout ${src})

message(STATUS "Linking SDL2 and SDL2_Image libraries")
target_link_libraries(WoollyBreakout ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
