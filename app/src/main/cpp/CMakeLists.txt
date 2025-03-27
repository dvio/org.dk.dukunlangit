# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("DukunLangit")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/DukunLangit)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Includes)

file(GLOB_RECURSE DUKUNLANGIT_SRC "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

include_directories(
#        ${INCLUDE_DIR}
        ${INCLUDE_DIR}/ImGui
        ${INCLUDE_DIR}/ImGui/backends
        ${INCLUDE_DIR}/StbImage
        ${INCLUDE_DIR}/KittyMemory
        ${INCLUDE_DIR}/nlohmann
        ${SRC_DIR}/Global
        ${SRC_DIR}/Core
        ${SRC_DIR}/Core/Utils
        ${SRC_DIR}/UI
)

file(GLOB RESOURCE_FILE_LIST RELATIVE ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_SOURCE_DIR}/resources/* )
foreach(RESOURCE_FILE ${RESOURCE_FILE_LIST})
    STRING(REGEX REPLACE "\\.[a-zA-Z0-9_]*" "" FILE_OBJ_NAME ${RESOURCE_FILE})
    add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/Objects/${FILE_OBJ_NAME}.o"
            DEPENDS ${CMAKE_SOURCE_DIR}/resources/${RESOURCE_FILE}
            COMMAND ${CMAKE_LINKER}
            ARGS -r -b binary -m aarch64elf ${RESOURCE_FILE} -o ${CMAKE_SOURCE_DIR}/Objects/${FILE_OBJ_NAME}.o
            COMMENT ARGS
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/resources
            COMMENT "Generating ${FILE_OBJ_NAME}.o"
    )
    set(INC_RES_OBJ_LIST ${INC_RES_OBJ_LIST} objects/${FILE_OBJ_NAME}.o)
endforeach()

file(GLOB CPP_INCLUDES
#        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/**/*.
#        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/**/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/ImGui/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/ImGui/backends/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/KittyMemory/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/StbImage/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/nlohmann/*.cpp

        ${SRC_DIR}/Core/*.cpp
        ${SRC_DIR}/Core/**/*.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/**/*.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/**/*.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/KittyMemory/KittyMemory/*.cpp
)

add_library(
        ${CMAKE_PROJECT_NAME}
        SHARED
        ${DUKUNLANGIT_SRC}
        ${CPP_INCLUDES}
        ${INC_RES_OBJ_LIST}
#        main.cpp
#        DukunLangit/ELFLoader/elfLoader.cpp
)
target_include_directories(
        ${CMAKE_PROJECT_NAME} PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/Utils/KittyMemory
        ${INCLUDE_DIR}
)

#add_definitions(-DkNO_KEYSTONE)
if (NOT kNO_KEYSTONE)
    set(keystone ${CMAKE_CURRENT_SOURCE_DIR}/Includes/KittyMemory/Deps/Keystone/libs-android/arm64-v8a/libkeystone.a)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${keystone})
endif()

find_library(log-lib log)
# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        android
        log
        dl
        GLESv3
        EGL
)