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
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE DUKUNLANGIT_SRC "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")
file(GLOB_RECURSE DUKUNLANGIT_INCLUDE_DIRS LIST_DIRECTORIES true "${SRC_DIR}/*")

file(GLOB_RECURSE EXT_INCLUDE_DIRS LIST_DIRECTORIES true "${INCLUDE_DIR}/*")

include_directories(
        ${DUKUNLANGIT_INCLUDE_DIRS}
        ${EXT_INCLUDE_DIRS}
)

add_library(
        ${CMAKE_PROJECT_NAME}
        SHARED
        ${DUKUNLANGIT_SRC}
#        main.cpp
#        DukunLangit/ELFLoader/elfLoader.cpp
)
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
)