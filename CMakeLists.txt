cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(ENVSDK $ENV{PLAYDATE_SDK_PATH})

if (NOT ${ENVSDK} STREQUAL "")
	# Convert path from Windows
	file(TO_CMAKE_PATH ${ENVSDK} SDK)
else()
	execute_process(
			COMMAND bash -c "egrep '^\\s*SDKRoot' $HOME/.Playdate/config"
			COMMAND head -n 1
			COMMAND cut -c9-
			OUTPUT_VARIABLE SDK
			OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

if (NOT EXISTS ${SDK})
	message(FATAL_ERROR "SDK Path not found; set ENV value PLAYDATE_SDK_PATH")
	return()
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(PLAYDATE_GAME_NAME uiLibrary)
set(PLAYDATE_GAME_DEVICE uiLibrary_DEVICE)

project(${PLAYDATE_GAME_NAME} C CXX ASM)

set(YOGA_LIB src/yoga/Yoga.cpp src/yoga/YGEnums.cpp src/yoga/YGValue.cpp src/yoga/YGStyle.cpp src/yoga/YGNodePrint.cpp src/yoga/YGNode.cpp src/yoga/YGLayout.cpp src/yoga/YGConfig.cpp src/yoga/Utils.cpp src/yoga/log.cpp src/yoga/internal/experiments.cpp src/yoga/event/event.cpp)
set(UI_LIB src/main.c src/yoga_bindings.cpp ${YOGA_LIB})
if (TOOLCHAIN STREQUAL "armgcc")
	add_executable(${PLAYDATE_GAME_DEVICE} ${SDK}/C_API/buildsupport/setup.c ${UI_LIB})
else()
	add_library(${PLAYDATE_GAME_NAME} SHARED ${UI_LIB})
endif()

include(${SDK}/C_API/buildsupport/playdate_game.cmake)

