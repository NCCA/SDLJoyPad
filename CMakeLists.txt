cmake_minimum_required(VERSION 3.12)
# Name of the project
project(SDLJoyPadBuild)
# This is the name of the Exe change this and it will change everywhere
set(TargetName SDLJoyPad)
find_package(SDL2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
# Set the name of the executable we want to build
add_executable(${TargetName})

# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include)
# use C++ 17
set(CMAKE_CXX_STANDARD 17)
target_sources(${TargetName} PRIVATE 
								${PROJECT_SOURCE_DIR}/src/main.cpp  
								${PROJECT_SOURCE_DIR}/src/Game.cpp  
								${PROJECT_SOURCE_DIR}/src/Rocket.cpp  
								${PROJECT_SOURCE_DIR}/src/StarMap.cpp			
								${PROJECT_SOURCE_DIR}/include/Game.h 
								${PROJECT_SOURCE_DIR}/include/Rocket.h  
								${PROJECT_SOURCE_DIR}/include/StarMap.h  
${PROJECT_SOURCE_DIR}/include/XBoxController.h
			)
add_compile_definitions(ADDLARGEMODELS)

# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Mac build")
	find_library(MACGL OpenGL)
	add_definitions(-DGL_SCILENCE_DEPRICATION)
	set ( PROJECT_LINK_LIBS ${MACGL} "-framework Metal" )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set ( PROJECT_LINK_LIBS -lGL)
endif()

# now add NGL specific values
target_link_directories(${TargetName} PRIVATE $ENV{HOME}/NGL/lib )

# add exe and link libs that must be after the other defines

target_link_libraries(${TargetName} PRIVATE ${PROJECT_LINK_LIBS} NGL fmt::fmt-header-only  )
target_link_libraries(${TargetName} PRIVATE  SDL2::SDL2-static)


add_custom_target(CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/models
		${CMAKE_BINARY_DIR}/models
		COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/textures
    ${CMAKE_BINARY_DIR}/textures


		)