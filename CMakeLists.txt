cmake_minimum_required(VERSION 3.11.0)
project(PowderGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# include(ClangFormat)
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
    option(INSTALL_GTEST "Enable installation of googletest." OFF)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp)

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