# tests/CMakeLists.txt
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

SET(HEADER_PATH ${CMAKE_SOURCE_DIR}/include/oatCore)
include_directories(${HEADER_PATH})

add_executable(test_orbitmodel test_orbitmodel.cpp)
target_link_libraries(test_orbitmodel oatCore) # 链接到你的动态库
add_test(NAME test_orbitmodel COMMAND test_orbitmodel)