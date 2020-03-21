# :arrow_double_down:  :computer:RemoteUnixTerminal:computer: :arrow_double_down:

![](https://github.com/Magistr-Y0da/RemoteUnixTerminal/blob/master/readme_pictures/MainConsole.PNG)

## RemoteUnixTerminal - Windows Client and UNIX Server

System requirements(Client):
OS: Windows 10 1604 and later

System requirements(Server):
OS: Gentoo Linux,
    Arch Linux,
    Debian Linux.

## Installation from Linux: :mag_right:
Dependecies:
- CMake https://cmake.org/download/
- Python3 https://www.python.org/downloads/

1. ```git clone https://github.com/Magistr-Y0da/RemoteUnixTerminal.git```
2. ```rm -R Client && rm -R readme_pictures && cd Server```
3. Build project =>  ```python3 ./Build.py```
4. Launch Server =>  ```./Server_RemoteUnixTerminal```
    
## Installation from Windows: :mag_right:

[![GitHub Releases](https://img.shields.io/github/downloads/Magistr-Y0da/RemoteUnixTerminal/v1.0/total)](https://github.com/Magistr-Y0da/RemoteUnixTerminal/releases/tag/v1.0)

- Binary files:

> 1. Extract from archive to folder
> 2. Launch Client => Client_RemoteUnixTerminal.exe

- Source files:
  - Dependecies:
    > - CMake https://cmake.org/download/
    > - MinGW-w64 http://mingw-w64.org/doku.php/download
  
  - Project assembly:
    > - Extract from archive to folder
    > - Delete "Client" and "readme_pictures" folders
    > - Go to "Client" foulder
    > - Create foulder "build"
    > - Go to "build" foulder
    > - Run command in cmd => ```cmake .. -G "MinGW Makefiles"```
    > - Run command in cmd => ```cmake --build .```

## Manual :mag_right:

Default "Server" login: root<br/>
Default "Server" password: root

In order to change the username and password you need to go:
```RemoteUnixTerminal/Server/data``` and open ```authorization.txt```.<br/>
First string it's "login". <br/>
Second string it's "password".<br/>
:warning::warning::warning:<br/>
Default "Server Port": 65322. (Doesn't change.)

In order to connect to the server, go to settings and indicate ip and port.

![](https://github.com/Magistr-Y0da/RemoteUnixTerminal/blob/master/readme_pictures/MainWindow.PNG)
![](https://github.com/Magistr-Y0da/RemoteUnixTerminal/blob/master/readme_pictures/SettingsWindow.PNG)

## Author: Magistr_Y0da
