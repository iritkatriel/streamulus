cmake_minimum_required(VERSION 3.3)
project(streamulus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(BOOST_ROOT "C:\\src\\boost_1_58_0")
set(BOOSTROOT "C:\\src\\boost_1_58_0")

find_package(Boost 1.58.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

include_directories(${Boost_INCLUDE_DIRS})
include_directories("src/")

add_definitions(-DUSE_MAIN -U__STRICT_ANSI__)

set(TEST_SOURCES
    test/operator_functors_test.cpp
    test/operator_subscribe_test.cpp
    test/tests.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests ${Boost_LIBRARIES})


add_executable(example_a examples/A_hello_world.cpp)
add_executable(example_b examples/B_common_subexpression.cpp)
add_executable(example_c examples/C_user_defined_functions_and_filters.cpp)
add_executable(example_d examples/D_sliding_window_function.cpp)

target_link_libraries(example_a ${Boost_LIBRARIES})
target_link_libraries(example_b ${Boost_LIBRARIES})
target_link_libraries(example_c ${Boost_LIBRARIES})
target_link_libraries(example_d ${Boost_LIBRARIES})

add_subdirectory(boost_test)
