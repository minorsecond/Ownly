cmake_minimum_required(VERSION 3.17)
project(Notch)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:\\msys64\\mingw64")
#set(Qt5_DIR "C:\\msys64\\mingw64\\lib\\cmake\\Qt5")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(SQLite3 REQUIRED)

include_directories(${SQLITE3_INCLUDE_DIRS})

add_executable(Notch src/main.cpp src/Database.cpp src/Database.h)
message(STATUS ${SQLite3_LIBRARIES})
target_link_libraries(Notch Qt5::Core Qt5::Widgets ${SQLite3_LIBRARIES})