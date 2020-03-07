cmake_minimum_required(VERSION 3.15)
project(Client_RemoteUnixTerminal VERSION 1.0.0 LANGUAGES C)

link_libraries(ws2_32 wsock32)

set(CMAKE_C_STANDARD 11)

add_compile_options(
        -Wall
        # -Wextra
        -Wpedantic
)

if(MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)

add_executable(Client_RemoteUnixTerminal
        source/MainWindow.c
        header/MainWindow.h
        source/MainConsole.c
        header/MainConsole.h
        source/SettingsWindow.c
        header/SettingsWindow.h
        resources/Resources.h
        resources/Resources.rc)

#set_target_properties(Client_RemoteUnixTerminal PROPERTIES WIN32_EXECUTABLE TRUE)

