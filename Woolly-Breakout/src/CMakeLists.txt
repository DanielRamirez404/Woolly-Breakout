cmake_minimum_required(VERSION 3.7)

project(WoollyBreakout)

message(STATUS "Building project with CMake...")

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
	include_directories("C:\\SDL2_Image\\include")

	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		message(STATUS "64-bit architecture detected")
		message(STATUS "Setting SDL2 and SDL2_Image library directories as the 64-bit default directories")
		set(SDL2_LIBRARIES "C:\\SDL2\\lib\\x64\\SDL2.lib;C:\\SDL2\\lib\\x64\\SDL2main.lib")
		set(SDL2_IMAGE_LIBRARIES "C:\\SDL2_Image\\lib\\x64\\SDL2_image.lib")

	else()
		message(STATUS "32-bit architecture detected")
		message(STATUS "Setting SDL2 and SDL2_Image library directories as the 32-bit default directories")
		set(SDL2_LIBRARIES "C:\\SDL2\\lib\\x86\\SDL2.lib;C:\\SDL2\\lib\\x86\\SDL2main.lib")	
		set(SDL2_IMAGE_LIBRARIES "C:\\SDL2_Image\\lib\\x86\\SDL2_image.lib")	
	endif()

endif()

message(STATUS "Creating executable from the project\'s source code")

file(GLOB src
	"main.cpp"
	"constants/*"
	"game/*"
	"game/ui/*"
	"game/map/*"
	"game/entities/*"
)

add_executable(WoollyBreakout ${src})

message(STATUS "Linking SDL2 and SDL2_Image libraries")
target_link_libraries(WoollyBreakout ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
