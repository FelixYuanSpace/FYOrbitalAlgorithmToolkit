cmake_minimum_required(VERSION 3.5.0)

SET(OAT_MAJOR_VERSION 0)
SET(OAT_MINOR_VERSION 0)
SET(OAT_PATCH_VERSION 1)

# Open OpenGL Test Render Solar System
OPTION(USE_OPENGL_TEST "Set to ON to enable OpenGL Test with Render Solar System.  Use OFF for disable." ON)


IF (USE_OPENGL_TEST)
    #set vcpkg toolchain file
    set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
ENDIF ()

project(OrbitAlgorithmToolkit VERSION ${OAT_MAJOR_VERSION}.${OAT_MINOR_VERSION}.${OAT_PATCH_VERSION} LANGUAGES C CXX)

# Dynamic vs Static Linking
OPTION(DYNAMIC_OAT "Set to ON to build OrbitAlgorithmToolkit for dynamic linking.  Use OFF for static." ON)
IF   (DYNAMIC_OAT)
    SET(OAT_SHARED_OR_STATIC "SHARED")
ELSE ()
    SET(OAT_SHARED_OR_STATIC "STATIC")
ENDIF()


set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include(CTest)
enable_testing()

add_subdirectory(tests)

add_subdirectory(${SOURCE_DIR}/oatCore)

#add_library(OrbitAlgorithmToolkit OrbitAlgorithmToolkit.cpp)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
