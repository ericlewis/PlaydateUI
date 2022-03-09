cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)

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

project(${PLAYDATE_GAME_NAME} C ASM)

set(YOGA_LIB src/yoga_bindings.c src/yoga/Yoga.c src/yoga/YGNodeList.c)
set(UI_LIB src/main.c ${YOGA_LIB})

if (TOOLCHAIN STREQUAL "armgcc")
	add_executable(${PLAYDATE_GAME_DEVICE} ${SDK}/C_API/buildsupport/setup.c ${UI_LIB})
else()
	add_library(${PLAYDATE_GAME_NAME} SHARED ${UI_LIB})
endif()

include(${SDK}/C_API/buildsupport/playdate_game.cmake)

