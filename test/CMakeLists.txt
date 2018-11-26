find_package(Catch2 REQUIRED)
enable_testing()

macro(add_unit_test test_name)
    add_executable(${test_name}.x ${test_name}.cpp)
    target_include_directories(${test_name}.x PRIVATE ${CMAKE_SOURCE_DIR}/src)
    add_test(${test_name} ${test_name}.x)
endmacro(add_unit_test)

add_unit_test(test_vec)
