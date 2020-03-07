cmake_minimum_required(VERSION 3.5.1)
project(Server C)

set(CMAKE_C_STANDARD 11)

add_executable(Server_RemoteUnixTerminal
              source/KernelServer.c
              header/KernelServer.h
              source/ServerTime.c
              header/ServerTime.h)

set(SHARED_LIB bin/libCD.so)

target_link_libraries(Server_RemoteUnixTerminal ${PROJECT_BINARY_DIR}/../${SHARED_LIB})
