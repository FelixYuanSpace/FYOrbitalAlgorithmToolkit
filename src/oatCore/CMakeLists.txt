# ADD MACRO DEFINED
IF(DYNAMIC_OAT)
    ADD_DEFINITIONS(-DOAT_LIB_DYNAMIC)
ELSE()
    ADD_DEFINITIONS(-DOAT_LIB_STAITC)
ENDIF()

SET(LIB_NAME oatCore)

SET(HEADER_PATH ${CMAKE_SOURCE_DIR}/include/${LIB_NAME})
include_directories(${HEADER_PATH})


# Set the source files for this directory
set(OAT_CORE_SRC
    orbitmodel.cpp
    orbitmodel_sgp4.cpp
    # Add other source files
)

# include thirdparty lib sgp4
include_directories("libsgp4")
file(GLOB LIBSGP4_SRC "libsgp4/*.cpp") 
list(APPEND OAT_CORE_SRC ${LIBSGP4_SRC})

# IF(USE_DEBUG)
#     ADD_DEFINITIONS(-DDEBUG)
#     #生成调试符号文件
#     #SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
# ENDIF()

# Create a library (either static or shared)
add_library(oatCore ${OAT_SHARED_OR_STATIC} ${OAT_CORE_SRC})


# 如果需要，为oatCore目标添加特定的编译选项
IF(USE_DEBUG)
    target_compile_options(oatCore PRIVATE "-g")
ENDIF()

# Link any necessary libraries
# target_link_libraries(orbit_calc other_libraries_if_necessary)