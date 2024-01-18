cmake_minimum_required(VERSION 3.0.0)
project(OrbitAlgorithmToolkit VERSION 0.1.0 LANGUAGES C CXX)

# Dynamic vs Static Linking
OPTION(DYNAMIC_OAT "Set to ON to build OrbitAlgorithmToolkit for dynamic linking.  Use OFF for static." ON)
IF   (DYNAMIC_OAT)
    SET(OAT_SHARED_OR_STATIC "SHARED")
ELSE ()
    SET(OAT_SHARED_OR_STATIC "STATIC")
ENDIF()


set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")



add_subdirectory(${SOURCE_DIR}/oatCore)

#add_library(OrbitAlgorithmToolkit OrbitAlgorithmToolkit.cpp)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
