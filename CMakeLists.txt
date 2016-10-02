CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

IF (NOT_CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF()

PROJECT(RogueDemonHunter)

SET(dot_VERSION_MAJOR 0)
SET(dot_VERSION_MINOR 1)

CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/Include/Config.h.in"
	"${PROJECT_SOURCE_DIR}/Include/Config.h"
)
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

SET(EXECUTABLE_NAME "RogueDemonHunter")
ADD_EXECUTABLE(${EXECUTABLE_NAME} Source/Main.cpp Source/Game.cpp Source/Menu.cpp Source/Entity.cpp Source/Settings.cpp Source/GameState.cpp Source/MenuState.cpp Source/Application.cpp Source/InputHandler.cpp Source/CommandMove.cpp Source/Interactable.cpp Source/FileManager.cpp)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake_Modules" ${CMAKE_MODULE_PATH})

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wall -Werror")

ADD_CUSTOM_COMMAND(TARGET ${EXECUTABLE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/Assets Assets)
		
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)
IF (SFML_FOUND)
	INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
ENDIF()