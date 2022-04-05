cmake_minimum_required(VERSION 3.11.0)
project(PowderGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# include(ClangFormat)

include_directories(src)
include_directories(external)

file(GLOB src_files
        "src/*.cpp"
        "src/*.hpp"
        "src/*.h"
)

file(GLOB element_files
        "src/elements/*.cpp"
        "src/elements/*.hpp"
        "src/elements/*.h"
)

file(GLOB_RECURSE extern_files
        "external/*.cpp"
        "external/*.hpp"
        "external/*.h"
)

# message("Src: ${src_files}")
# message("Elements: ${element_files}")
# message("Extern: ${extern_files}")

add_executable(${PROJECT_NAME} src/main.cpp ${src_files} ${element_files} ${extern_files})

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