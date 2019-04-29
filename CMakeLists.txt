cmake_minimum_required(VERSION 3.9.4)

project(cpp-guards VERSION 0.1.0)

message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


option(UNITTEST "Build unit tests" ON)
message(STATUS "Unit Tests : ${UNITTEST}")

if( CMAKE_BUILD_TYPE )
    message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
else()
    message(STATUS "Build Type : None")
endif()



set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall
                    -Wextra
                    -Werror
                    -pedantic
                    -Wshadow
                    -Wold-style-cast
                    )

add_library(guards INTERFACE)
target_include_directories(guards INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:include>
                            )


if( UNITTEST )
    enable_testing()
    subdirs(test)
endif()


include(Install)
