
message(STATUS "Building Unit Tests ${UNITTEST}")

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

function(add_test_suite name src)
    add_executable(${name} ${src})
    add_test(NAME ${name} COMMAND ${name})

    target_include_directories(${name} SYSTEM PUBLIC
                                ${GTest_INCLUDE_DIR}
                                ${GMock_INCLUDE_DIR}
                                )
    target_link_libraries(${name} ${GTest_LIBRARIES}
                                    ${GMock_LIBRARY}
                                    ${CMAKE_THREAD_LIBS_INIT}
                                    )
endfunction()

add_test_suite(ScopeGuardTest ScopeGuardTest.cpp)
add_test_suite(TransactionGuardTest TransactionGuardTest.cpp)


add_custom_target(unittest ScopeGuardTest
                        COMMAND TransactionGuardTest
                        COMMENT "Running unittests\n\n"
                        VERBATIM
                        )
