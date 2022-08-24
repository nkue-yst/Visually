cmake_minimum_required(VERSION 3.10)
project(PLC)

### Setup C++ project ###
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall")

### Define cmake options ###
option(PLC_OPTIMIZE "Optimization at compile time" OFF)
if(PLC_OPTIMIZE)
    set(CMAKE_CXX_FLAGS "-O3")
endif()

option(PLC_DEBUG "" ON)
if(PLC_DEBUG)
    set(CMAKE_CXX_FLAGS "-g")
endif()

### Setup main sources ###
file(GLOB PLC_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(plc ${PLC_SRC})
