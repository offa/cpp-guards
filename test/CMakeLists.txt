
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "catch")

add_library(Trompeloeil INTERFACE)
target_include_directories(Trompeloeil INTERFACE "trompeloeil")

add_library(TestMain TestMain.cpp)
target_link_libraries(TestMain Catch Trompeloeil)


function(add_test_suite name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} TestMain)
    add_test(${name} ${name})
endfunction()


add_test_suite(ScopeGuardTest ScopeGuardTest.cpp)
add_test_suite(TransactionGuardTest TransactionGuardTest.cpp)


add_custom_target(unittest ScopeGuardTest
                        COMMAND TransactionGuardTest
                        COMMENT "Running unittests\n\n"
                        VERBATIM
                        )
