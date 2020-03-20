# RemoteUnixTerminal

![](https://github.com/Magistr-Y0da/RemoteUnixTerminal/blob/master/readme_pictures/MainConsole.PNG)

## RemoteUnixTerminal - Windows Client and UNIX Server

System requirements(Client):
OS: Windows 10 1604 and later

System requirements(Server):
OS: Gentoo Linux,
    Arch Linux,
    Debian Linux.

## Installation from Linux:
Dependecies:
- CMake https://cmake.org/download/
- Python3 https://www.python.org/downloads/

1. ```git clone https://github.com/Magistr-Y0da/RemoteUnixTerminal.git```
2. ```rm -R Client && rm -R readme_pictures && cd Server```
3. Build project =>  ```python3 ./Build.py```
4. Launch Server =>  ```./Server_RemoteUnixTerminal```
    
## Installation from Windows:

[![GitHub Releases](https://img.shields.io/github/downloads/Magistr-Y0da/RemoteUnixTerminal/v1.0/total)](https://github.com/Magistr-Y0da/RemoteUnixTerminal/releases/tag/v1.0)

- Binary files:

> 1. Extract from archive to folder
> 2. Launch Client => Client_RemoteUnixTerminal.exe

- Source files:
> Dependecies:
> - CMake https://cmake.org/download/
> - MinGW-w64 http://mingw-w64.org/doku.php/download

> 1. Extract from archive to folder
> 2. Delete "Client" and "readme_pictures" folders
> 3. Go to "Client" foulder
> 4. Create foulder "build"
> 5. Go to "build" foulder
> 6. Run command in cmd => ```cmake .. -G "MinGW Makefiles"```
> 7. Run command in cmd => ```cmake --build .```
