cmake_minimum_required(VERSION 3.17)
project(Ownly)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:\\msys64\\mingw64")
list(APPEND CMAKE_PREFIX_PATH "C:\\msys64\\mingw64\\lib\\cmake\\Qt5")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

message("CMAKE_FIND_LIBRARY_SUFFIXES: ${CMAKE_FIND_LIBRARY_SUFFIXES}")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Catch2 REQUIRED)

if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
else()
    message("SQLite3 not found!")
    message("SQLite3 include dir=${SQLITE3_INCLUDE_DIR}")
    message("SQLite3 library dir=${SQLITE3_LIBRARY}")
endif(SQLITE3_FOUND)

include_directories(${SQLITE3_INCLUDE_DIRS})

add_executable(Ownly src/main.cpp src/Database.cpp src/Database.h)
add_executable(database_functions_test src/Database.cpp test/test-main.cpp test/test_database_functions.cpp)
message(STATUS ${SQLite3_INCLUDE_DIRS})
target_include_directories(Ownly PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries(Ownly Qt5::Core Qt5::Widgets SQLite3)

target_include_directories(database_functions_test PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries(database_functions_test SQLite3)
include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(database_functions_test)