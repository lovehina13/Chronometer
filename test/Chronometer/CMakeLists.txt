find_package(GTest)

add_executable(ChronometerTest BaseTest.cpp ChronometerTest.cpp)

target_include_directories(ChronometerTest PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(ChronometerTest PUBLIC Chronometer GTest::gtest GTest::gtest_main)

gtest_discover_tests(ChronometerTest)
