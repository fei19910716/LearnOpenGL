cmake_minimum_required(VERSION 3.16)
project(Learn_OpenGL)
set(target Learn_OpenGL)

# glfw3 library
ADD_LIBRARY(glfw3 STATIC IMPORTED)
SET_TARGET_PROPERTIES(glfw3 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glfw/lib/libglfw3.a)

set(GLFW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glfw)
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/glad.h" "${GLFW_SOURCE_DIR}/deps/glad.c")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty)
include_directories(${GLFW_SOURCE_DIR}/include)
include_directories(${GLFW_SOURCE_DIR}/deps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/assimp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ffmpeg/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ffmpeg/include/movie)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/assimp/code)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/ffmpeg TOOL_SRC)
add_executable(${target}
        ${GLAD_GL}
        ${TOOL_SRC}
        main.cpp)
add_subdirectory(3rdParty)
find_library(OpenGL_LIBRARY OpenGL )
find_library(Cocoa_LIBRARY Cocoa )
find_library(IOKit_LIBRARY IOKit )

list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ffmpeg/mac/libavcodec.a)
list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ffmpeg/mac/libavutil.a)
list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ffmpeg/mac/libavformat.a)
list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ffmpeg/mac/libswscale.a)
list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ffmpeg/mac/libswresample.a)
list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/libz/libz.a)

target_link_libraries(${target} ${libs} ${OpenGL_LIBRARY} ${Cocoa_LIBRARY} ${IOKit_LIBRARY} assimp glfw3)

set(custom_output_dir ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${custom_output_dir})
set_target_properties(${target} PROPERTIES LINK_FLAGS_RELEASE -s)