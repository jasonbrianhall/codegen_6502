cmake_minimum_required(VERSION 3.5)

project(smbc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -std=c++11 -Wno-c++11-narrowing -fpermissive")

set(SOURCE_FILES
    source/Configuration.cpp
    source/Main.cpp
    source/Emulation/APU.cpp
    source/Emulation/Controller.cpp
    source/Emulation/MemoryAccess.cpp
    source/Emulation/PPU.cpp
    source/SMB/SMB.cpp
    source/SMB/SMBData.cpp
    source/SMB/SMBEngine.cpp
    source/Util/Video.cpp
    source/Util/VideoFilters.cpp
    source/SMBRom.cpp)

find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(smbc ${SOURCE_FILES})
target_link_libraries(smbc ${SDL2_LIBRARY} ${SDL2_LIBRARIES})
