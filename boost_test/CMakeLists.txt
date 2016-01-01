

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB testFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

FOREACH(testfile ${testFiles})
    STRING(REGEX REPLACE ".cpp\$" "" testname "${testfile}")
    MESSAGE(STATUS "Process test: ${testname}")

    ADD_EXECUTABLE(${testname} ${testname}.cpp)
    TARGET_LINK_LIBRARIES(${testname} ${Boost_LIBRARIES})
ENDFOREACH(testfile)






