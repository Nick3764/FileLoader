cmake_minimum_required(VERSION 3.27)
project(Loader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH  "F:\\Ambiente_di_Programmazione\\Qt\\6.6.1\\mingw_64\\lib\\cmake\\")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
add_subdirectory(test)

add_executable(Loader main.cpp
        Observer.h
        Subject.h
        FileLoader.h
        FileLoader.cpp
        GUI.h
        GUI.cpp
        test/runAllTests.cpp
        test/FileLoaderTest.cpp
        test/GUITest.cpp
)

target_link_libraries(Loader Qt6::Widgets)