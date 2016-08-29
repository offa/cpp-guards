cmake_minimum_required(VERSION 2.8.11)

project(cpp-guards)
set(PROJECT_VERSION, 0.0.1-dev)

option(UNITTEST "Build unit tests" ON)


message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Cpp14)

include_directories("include")

add_definitions(-Wall -Wextra -Werror -pedantic -Wshadow)

if( UNITTEST )
    enable_testing()
    subdirs(test)
endif()
