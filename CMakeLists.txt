cmake_minimum_required(VERSION 3.13)
project(lvgl)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(/usr/local/include)

file(GLOB_RECURSE INCLUDES "./*.h" )

SET(CMAKE_CXX_FLAGS "-O0 -g -ggdb")
SET(CMAKE_C_FLAGS "-O0 -g")

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(lvgl)
add_executable(main main.c mouse_cursor_icon.c ${SOURCES} ${INCLUDES})
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
target_link_libraries(main PRIVATE lvgl lvgl::examples ${SDL2_LIBRARIES})

target_compile_options(lvgl PRIVATE -Werror -Werror=float-conversion)
