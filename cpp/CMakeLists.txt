cmake_minimum_required(VERSION 3.12)

project (game_of_life)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

file (GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.h")

set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES INCLUDE_DIRS)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
