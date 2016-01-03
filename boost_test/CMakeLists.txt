# to run the tests: cmake, then make, then ctest

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(UNITTEST CXX)
SET(CMAKE_VERBOSE_MAKEFILE ON)

ADD_CUSTOM_TARGET(alltests ALL)

FILE(GLOB testFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

FOREACH (testfile ${testFiles})
    GET_FILENAME_COMPONENT(testname ${testfile} NAME_WE)
    MESSAGE(STATUS "Process test: ${testname}")

    ADD_EXECUTABLE(${testname} ${testfile})
    TARGET_LINK_LIBRARIES(${testname} ${Boost_LIBRARIES})

    ADD_TEST(NAME ${testname} COMMAND ${testname})
    ADD_DEPENDENCIES(alltests ${testname})
ENDFOREACH (testfile)

