// ----------------------------------------------------------------------------
// $File: MainWindow.h $
// $Date: 02.01.2020 $
// $Revision: 02.01.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------

#ifndef CLIENT_MAINCONSOLE_H
#define CLIENT_MAINCONSOLE_H

#include <windows.h>
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <winsock2.h>

extern int16_t Main_Console(HWND MainConsoleClient, const char *login, const char *password);

extern ssize_t send_all(SOCKET s, const char * buf, ssize_t len, int flags);
extern ssize_t recv_all(SOCKET s, char * buf, ssize_t len, int flags);

#define SIZE_LOGO_CLIENT_CONSOLE 1024

#define MAIN_CONSOLE_CLIENT_NAME L"RemoteUnixTerminal(Client)"
#define PATH_LOGO_CLIENT_CONSOLE "../decor/LogoClientConsole"
#define PATH_CLIENT_OUTPUT "../data/client_output"

#define MESSAGE_BOX_ERROR_STYLE ( (unsigned)MB_OK | \
                                  (unsigned)MB_ICONERROR | \
                                  (unsigned)MB_APPLMODAL | \
                                  (unsigned)MB_SERVICE_NOTIFICATION | \
                                  (unsigned)MB_SETFOREGROUND )

#define CLIENT_OUTPUT_FILE_FLAGS ( (unsigned)GENERIC_READ | \
                                   (unsigned)GENERIC_WRITE )

#define WHITE_COLOR ( (unsigned)FOREGROUND_RED | \
                      (unsigned)FOREGROUND_GREEN | \
                      (unsigned)FOREGROUND_BLUE )

#define AQUA_COLOR ( (unsigned)FOREGROUND_BLUE | \
                     (unsigned)FOREGROUND_GREEN )

#define JUMP( name_label ) \
            goto name_label

#endif //CLIENT_MAINCONSOLE_H
