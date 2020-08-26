cmake_minimum_required(VERSION 3.17)
project(Notch)

set(Qt5_DIR "C:\\msys64\\mingw64\\lib\\cmake\\Qt5")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(Notch src/main.cpp)
target_link_libraries(Notch Qt5::Core Qt5::Widgets)