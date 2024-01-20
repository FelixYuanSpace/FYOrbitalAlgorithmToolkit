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

# Create a library (either static or shared)
add_library(oatCore ${OAT_SHARED_OR_STATIC} ${OAT_CORE_SRC})

# Link any necessary libraries
# target_link_libraries(orbit_calc other_libraries_if_necessary)