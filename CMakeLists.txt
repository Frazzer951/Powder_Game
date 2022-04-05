cmake_minimum_required(VERSION 3.11.0)
project(PowderGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# include(ClangFormat)

file(DOWNLOAD
        https://raw.githubusercontent.com/OneLoneCoder/olcPixelGameEngine/master/olcPixelGameEngine.h
        ${CMAKE_SOURCE_DIR}/external/olcPixelGameEngine/olcPixelGameEngine.h)

include_directories(src)
include_directories(external)

add_executable(${PROJECT_NAME} src/main.cpp src/olcPixelGameEngine.cpp)

#target_clangformat_setup(${PROJECT_NAME})

#add_custom_target(clangtidy
#        COMMAND
#        clang-tidy
#        -p ./build
#        --fix-notes
#        --fix-errors
#        ./src/*
#        WORKING_DIRECTORY
#        ${CMAKE_SOURCE_DIR}
#        COMMENT
#        "Running Clang Tidy..."
#        )