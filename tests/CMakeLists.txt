# tests/CMakeLists.txt


IF (USE_OPENGL_TEST)
    #set freeglut path for windows
    set(VCPKG_ROOT "D:/devTools/vcpkg")
    set(VcpkgInclude_Path ${VCPKG_ROOT}/installed/x64-windows/include)
    set(freeglut_DIR ${VCPKG_ROOT}/installed/x64-windows/share/freeglut)
    set(glfw3_DIR ${VCPKG_ROOT}/installed/x64-windows/share/glfw3)
    include_directories(${VcpkgInclude_Path})

    find_package(OpenGL REQUIRED)
    find_package(PkgConfig REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(freeglut REQUIRED)

    link_directories(${VCPKG_ROOT}/installed/x64-windows/lib)



ENDIF()

SET(HEADER_PATH ${CMAKE_SOURCE_DIR}/include/oatCore)

include_directories(${HEADER_PATH})

add_executable(test_orbitmodel test_orbitmodel.cpp)
target_link_libraries(test_orbitmodel oatCore glfw freeglut glu32 opengl32 gdi32 user32 kernel32)
add_test(NAME test_orbitmodel COMMAND test_orbitmodel)

IF (USE_OPENGL_TEST)
    add_custom_command(TARGET test_orbitmodel POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${VCPKG_ROOT}/installed/x64-windows/bin/glfw3.dll
        $<TARGET_FILE_DIR:test_orbitmodel>)
    add_custom_command(TARGET test_orbitmodel POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${VCPKG_ROOT}/installed/x64-windows/bin/freeglut.dll
        $<TARGET_FILE_DIR:test_orbitmodel>)
    
ENDIF()