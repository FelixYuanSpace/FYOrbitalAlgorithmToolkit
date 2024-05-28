# ADD MACRO DEFINED
IF(DYNAMIC_OAT)
    ADD_DEFINITIONS(-DOAT_LIB_DYNAMIC)
ELSE()
    ADD_DEFINITIONS(-DOAT_LIB_STAITC)
ENDIF()

SET(LIB_NAME oatCore)

SET(HEADER_PATH ${CMAKE_SOURCE_DIR}/include/${LIB_NAME})
SET(OAT_CORE_SRC_PATH ${CMAKE_SOURCE_DIR}/src/oatCore)



include_directories(${HEADER_PATH})
include_directories(${HEADER_PATH}/coord)
include_directories(${HEADER_PATH}/math)
include_directories(${HEADER_PATH}/sgp4)

# Set the source files for this directory
set(OAT_CORE_SRC
    ${OAT_CORE_SRC_PATH}/orbitmodel.cpp
    ${OAT_CORE_SRC_PATH}/orbitmodel_sgp4.cpp
    ${OAT_CORE_SRC_PATH}/coord/coord.cpp
    ${OAT_CORE_SRC_PATH}/libsgp4/sgp4.cpp
    # Add other source files
)


#增加导出宏定义
ADD_DEFINITIONS(-DOAT_CORE_EXPORTS)

# IF(USE_DEBUG)
#     ADD_DEFINITIONS(-DDEBUG)
#     #生成调试符号文件
#     #SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
# ENDIF()


#file(GLOB_RECURSE oat_header_files  ${HEADER_PATH}/*.h )
#追加include coord math
file(GLOB_RECURSE oat_header_files  ${HEADER_PATH}/libsgp4/*.h ${HEADER_PATH}/coord/*.h ${HEADER_PATH}/math/*.h ${HEADER_PATH}/*.h ) 
source_group("Header Files" FILES ${oat_header_files}) 

# Create a library (either static or shared)
add_library(oatCore ${OAT_SHARED_OR_STATIC} ${OAT_CORE_SRC} ${oat_header_files})



# 如果需要，为oatCore目标添加特定的编译选项
IF(USE_DEBUG)
    target_compile_options(oatCore PRIVATE "-g")
ENDIF()

# Link any necessary libraries
# target_link_libraries(orbit_calc other_libraries_if_necessary)