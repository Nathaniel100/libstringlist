
cmake_minimum_required(VERSION 3.10)
project(libstringlist C)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})

add_library(stringlist
def.h
refcnt.h
string_list.c
string_list.h
string_slice.c
string_slice.h
)


add_subdirectory(unittest)

