cmake_minimum_required(VERSION 2.8)

project(mod_q)

file(GLOB sources *.c *.cpp)

include_directories(/usr/include/apr-1 /usr/include/httpd)

add_library(mod_q SHARED ${sources})
