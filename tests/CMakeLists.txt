include_directories(../src)

include_directories(.)

add_executable(tests
    # point tests
    point_test.cpp
    point_array_test.cpp
    # point sources    
    ../src/xipoint.cpp
    ../src/xipoint.h
    # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc
)
