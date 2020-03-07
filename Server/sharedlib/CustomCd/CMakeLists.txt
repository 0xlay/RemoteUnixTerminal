cmake_minimum_required(VERSION 3.5.1)
project(CDlib C)

set(CMAKE_C_STANDARD 99)

add_library(CD SHARED servercd.c servercd.h)
