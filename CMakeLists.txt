cmake_minimum_required(VERSION 3.23)

project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES src/main.cpp)
set(EXT_FILES ext/glad.c)

add_executable(opengl ${SRC_FILES} ${EXT_FILES})
target_include_directories(opengl PUBLIC include)

if (WIN32)
target_link_directories(opengl PUBLIC lib)
endif()

target_link_libraries(opengl glfw3)