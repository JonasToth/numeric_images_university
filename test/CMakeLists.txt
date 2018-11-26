find_package(Catch2 REQUIRED)
enable_testing()

include(CTest)
include(Catch)
macro(add_unit_test test_name)
    add_executable(${test_name}.x ${test_name}.cpp catch_main.cpp)
    target_link_libraries(${test_name}.x Catch2::Catch2)
    target_include_directories(${test_name}.x PRIVATE ${CMAKE_SOURCE_DIR}/src)
    catch_discover_tests(${test_name}.x)
endmacro(add_unit_test)

add_unit_test(test_vec)
add_unit_test(test_writeDat)
