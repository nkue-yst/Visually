cmake_minimum_required(VERSION 3.10)
project(Visually)

### Setup C++ project ###
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall")

### Define cmake options ###
option(Visually_OPTIMIZE "Optimization at compile time" OFF)
if(Visually_OPTIMIZE)
    set(CMAKE_CXX_FLAGS "-O3")
endif()

option(Visually_DEBUG "" ON)
if(Visually_DEBUG)
    set(CMAKE_CXX_FLAGS "-g")
endif()

### Setup main sources ###
file(GLOB Visually_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(Visually ${Visually_SRC})

### Setup SDL2 ###
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/SDL)
set(SDL2_DIR ${CMAKE_BINARY_DIR}/thirdparty/SDL)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(Visually ${SDL2_STATIC_LIBRARIES})
