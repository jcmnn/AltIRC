cmake_minimum_required(VERSION 2.7)
project(Lua)

file(GLOB Lua_SOURCES src/*.c)

add_library(Lua ${Lua_SOURCES})
target_link_libraries(Lua m)

set(Lua_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)