
message(STATUS "Building Unit Tests ${UNITTEST}")

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

macro(_add_test _NAME _SRC)
    add_executable(${_NAME} ${_SRC})
    add_test(NAME ${_NAME} COMMAND ${_NAME})

    target_include_directories(${_NAME} SYSTEM PUBLIC
                                ${GTest_INCLUDE_DIR}
                                ${GMock_INCLUDE_DIR}
                                )
    target_link_libraries(${_NAME} ${GTest_LIBRARIES}
                                    ${GMock_LIBRARY}
                                    ${CMAKE_THREAD_LIBS_INIT}
                                    )
endmacro()

_add_test(ScopeGuardTest ScopeGuardTest.cpp)
_add_Test(TransactionGuardTest TransactionGuardTest.cpp)


add_custom_target(unittest ScopeGuardTest
                        COMMAND TransactionGuardTest
                        COMMENT "Running unittests\n\n"
                        VERBATIM
                        )
