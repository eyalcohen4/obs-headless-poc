cmake_minimum_required(VERSION 3.10)

project(obs_headless_poc)

add_definitions(-DDL_OPENGL="${CMAKE_CURRENT_SOURCE_DIR}/obs-studio/build/libobs-opengl/libobs-opengl")
add_definitions(-DROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(obs_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/obs-studio/libobs/)
set(obs_lib_dir     ${CMAKE_CURRENT_SOURCE_DIR}/obs-studio/build/libobs/)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(/home/myplay/dev/obs-headless-poc/obs-studio/libobs)
link_directories(/home/myplay/dev/obs-headless-poc/obs-studio/build/libobs)

include_directories(/home/myplay/dev/obs-headless-poc/obs-studio/libobs-opengl)
link_directories(/home/myplay/dev/obs-headless-poc/obs-studio/build/libobs-opengl)

file(GLOB SOURCES 
  "./src/*.h"
  "./src/*.cpp")

add_executable(app ${SOURCES})
target_link_libraries(app /home/myplay/dev/obs-headless-poc/obs-studio/build/libobs/libobs.so /home/myplay/dev/obs-headless-poc/obs-studio/build/libobs-opengl/libobs-opengl.so)