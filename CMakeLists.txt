cmake_minimum_required(VERSION 3.11.0)
project(PowderGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
include_directories(external)
include_directories(include)

file(GLOB src_files
        "src/*.cpp"
        "src/*.hpp"
        "src/*.h"
)

file(GLOB_RECURSE include_files
        "include/*.cpp"
        "include/*.hpp"
        "include/*.h"
)

file(GLOB_RECURSE extern_files
        "external/*.cpp"
        "external/*.hpp"
        "external/*.h"
)

message("Src: ${src_files}")
message("Include: ${include_files}")
message("Extern: ${extern_files}")

add_executable(${PROJECT_NAME} src/main.cpp ${src_files} ${include_files} ${extern_files})
