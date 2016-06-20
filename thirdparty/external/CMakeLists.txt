# Build system for a subset of third party libraries required by displaz.

set(CMAKE_BUILD_TYPE "Release" CACHE STRING
    "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel."
)

if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "-std=c++0x"
        CACHE STRING "Flags used by the compiler during all build types.")
endif()

project(external_libs)

cmake_minimum_required(VERSION 2.8)

set(DOWNLOAD_DIR "${PROJECT_SOURCE_DIR}/downloads"
    CACHE PATH "Location for downloaded source archives")
set(THIRDPARTY_INSTALL_PREFIX "dist"
    CACHE PATH "Location to install third party libraries")

set(CMAKE_INSTALL_PREFIX ${THIRDPARTY_INSTALL_PREFIX})

include(ExternalProject)

ExternalProject_Add(
    ilmbase
    URL http://download.savannah.nongnu.org/releases/openexr/ilmbase-2.2.0.tar.gz
    URL_MD5 b540db502c5fa42078249f43d18a4652
    CMAKE_ARGS
        -D CMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
        -D CMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -D CMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -D NAMESPACE_VERSIONING:BOOL=OFF
        -D BUILD_SHARED_LIBS:BOOL=OFF
    INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
    DOWNLOAD_DIR "${DOWNLOAD_DIR}"
)

ExternalProject_Add(
    laslib
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/LAStools
    CMAKE_ARGS
        -D CMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
        -D CMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -D CMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
    DOWNLOAD_DIR "${DOWNLOAD_DIR}"
)

ExternalProject_Add(
    nanogui
    GIT_REPOSITORY https://github.com/r-chris/nanogui.git
    GIT_TAG a081770bd0dbe2a92f6b78fcc171c1df279bf093
    GIT_SUBMODULES
    CMAKE_ARGS
        -D NANOGUI_BUILD_SHARED:BOOL=OFF
        -D NANOGUI_BUILD_PYTHON:BOOL=OFF
        -D NANOGUI_BUILD_EXAMPLE:BOOL=OFF
        -D CMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
        -D CMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -D CMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
    DOWNLOAD_DIR "${DOWNLOAD_DIR}"
)

# ExternalProject_Add(
#     libigl
#     GIT_REPOSITORY https://github.com/r-chris/libigl.git
#     GIT_TAG d562972b1c4d564a8153c7b1443650d019bcb3c4
#     GIT_SUBMODULES
#     PREFIX "optional"
#     CMAKE_ARGS
#         -D LIBIGL_WITH_ANTTWEAKBAR:BOOL=OFF
#         -D LIBIGL_WITH_NANOGUI:BOOL=ON
#         -D CMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
#         -D CMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
#         -D CMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
#     INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
#     DOWNLOAD_DIR "${DOWNLOAD_DIR}"
# )

# ExternalProject_Add(
#     libjson
#     URL http://downloads.sourceforge.net/project/libjson/libjson_7.6.1.zip
#     URL_MD5 82f3fcbf9f8cf3c4e25e1bdd77d65164
#     TIMEOUT ${DOWNLOAD_TIMEOUT}
#     DOWNLOAD_DIR ${THIRDPARTY_DOWNLOAD_DIR}
#     PATCH_COMMAND cp ${ThirdParty_SOURCE_DIR}/libjson/CMakeLists.txt . && patch -p1 < ${ThirdParty_SOURCE_DIR}/libjson/config.patch
#     CONFIGURE_COMMAND ${CCMAKE_COMMAND} ${SOURCE_DIR}
#     CMAKE_ARGS
#         -D CMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
#         -D CMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
#         -D CMAKE_INSTALL_PREFIX:PATH=${LIBJSON_INSTALL_DIR}
#     INSTALL_COMMAND make install
#     BUILD_IN_SOURCE 0
# )

# URL https://github.com/miloyip/rapidjson/archive/v1.0.2.zip
# URL_MD5 446a0673d58766e507d641412988dcaa

ExternalProject_Add(
    rapidjson
    GIT_REPOSITORY https://github.com/miloyip/rapidjson
    GIT_TAG 1c087b77cb7eb40a40aaf1d0f28feedc2d6e42ee
    CMAKE_ARGS
        -D CMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
        -D CMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -D CMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
    DOWNLOAD_DIR "${DOWNLOAD_DIR}"
)
