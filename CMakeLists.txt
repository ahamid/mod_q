cmake_minimum_required(VERSION 2.8)

project(mod_q)

file(GLOB sources src/*.c src/*.cpp)

include_directories(/usr/include/apr-1 /usr/include/httpd)

add_library(mod_q SHARED ${sources})

set_target_properties(mod_q PROPERTIES LIBRARY_OUTPUT_DIRECTORY "bin/Debug")
