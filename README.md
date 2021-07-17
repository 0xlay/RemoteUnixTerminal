<h1 align="center">:arrow_double_down:  :computer:RemoteUnixTerminal:computer: :arrow_double_down:</h1>

![](https://github.com/0xlay/RemoteUnixTerminal/blob/master/readme_pictures/MainConsole.PNG)

<h2 align="center">:arrow_double_down: RemoteUnixTerminal - Windows Client and UNIX Server :arrow_double_down:</h2>

### About: :pencil:

This program allows you to organize remote access to a computer terminal(Linux).

### System requirements(Client): :telephone_receiver:
OS: Windows 10 1604 and later

### System requirements(Server): :computer:
OS: Gentoo Linux,
    Arch Linux,
    Debian Linux.

## Installation from Linux: :mag_right:
Dependecies:
- CMake https://cmake.org/download/
- Python3 https://www.python.org/downloads/

1. ```git clone https://github.com/0xlay/RemoteUnixTerminal.git```
2. ```rm -R Client && rm -R readme_pictures && cd Server```
3. Build project =>  ```python3 ./Build.py```
4. Launch Server =>  ```./Server_RemoteUnixTerminal```
    
## Installation from Windows: :mag_right:

[![GitHub Releases](https://img.shields.io/github/downloads/0xlay/RemoteUnixTerminal/v1.0/total)](https://github.com/0xlay/RemoteUnixTerminal/releases/tag/v1.0)

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

<p align="center"> 
<img src="https://github.com/0xlay/RemoteUnixTerminal/blob/master/readme_pictures/MainWindow.PNG">
<img src="https://github.com/0xlay/RemoteUnixTerminal/blob/master/readme_pictures/SettingsWindow.PNG">
</p>

### Author: 0xlay
