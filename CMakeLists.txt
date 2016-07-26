cmake_minimum_required(VERSION 2.7)
project(AltIRC)

add_subdirectory(lib/lua)
include_directories(lib/lua/src)
add_subdirectory(lib/toluapp)
include_directories(lib/toluapp/include)
add_subdirectory(src)