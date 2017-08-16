cmake_minimum_required(VERSION 3.2)

project(cpp-guards VERSION 0.0.1)

option(UNITTEST "Build unit tests" ON)


message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Cpp14)

add_definitions(-Wall
                -Wextra
                -Werror
                -pedantic
                -Wshadow
                -Wold-style-cast
                )

include_directories("include")


if( UNITTEST )
    enable_testing()
    subdirs(test)
endif()
