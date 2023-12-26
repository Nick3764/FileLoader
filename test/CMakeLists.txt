cmake_minimum_required(VERSION 3.27)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp FileLoaderTest.cpp GUITest.cpp ../FileLoader.h ../FileLoader.cpp ../GUI.h ../GUI.cpp)
add_executable(runTests ${TEST_SOURCE_FILES})
target_link_libraries(runTests gtest gtest_main Qt6::Widgets)
