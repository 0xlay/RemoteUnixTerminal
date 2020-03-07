// ----------------------------------------------------------------------------
// $File: MainWindow.h $
// $Date: 30.12.2019 $
// $Revision: 05.01.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------

#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <windows.h>
#include <tchar.h>
#include <stdint.h>

extern long WINAPI WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

#define MM_TO_PIXEL 3.793627

#define MAIN_WINDOW_CLIENT_WIDTH 400
#define MAIN_WINDOW_CLIENT_HEIGHT 500

#define EDIT_LOGIN_CLIENT_WIDTH 160
#define EDIT_LOGIN_CLIENT_HEIGHT 20

#define EDIT_PASSWORD_CLIENT_WIDTH 160
#define EDIT_PASSWORD_CLIENT_HEIGHT 20

#define BUTTON_SETTINGS_CLIENT_WIDTH 160
#define BUTTON_SETTINGS_CLIENT_HEIGHT 40

#define BUTTON_CONNECT_CLIENT_WIDTH 160
#define BUTTON_CONNECT_CLIENT_HEIGHT 40

#define BUTTON_DISCONNECT_CLIENT_WIDTH 160
#define BUTTON_DISCONNECT_CLIENT_HEIGHT 40

#define WND_MAIN_WINDOW_CLIENT_STYLE ( (unsigned)CS_HREDRAW | \
                                       (unsigned)CS_VREDRAW )

#define MAIN_WINDOW_CLIENT_STYLE ( (unsigned)WS_OVERLAPPED | \
                                   (unsigned)WS_CAPTION | \
                                   (unsigned)WS_SYSMENU | \
                                   (unsigned)WS_MINIMIZEBOX )

#define EDIT_LOGIN_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                  (unsigned)WS_VISIBLE | \
                                  (unsigned)WS_BORDER | \
                                  (unsigned)ES_LEFT )

#define EDIT_PASSWORD_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                     (unsigned)WS_VISIBLE | \
                                     (unsigned)WS_BORDER | \
                                     (unsigned)ES_LEFT | \
                                     (unsigned)ES_PASSWORD )

#define BUTTON_SETTINGS_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                      (unsigned)WS_VISIBLE | \
                                      (unsigned)WS_BORDER | \
                                      (unsigned)BS_CENTER )

#define BUTTON_CONNECT_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                      (unsigned)WS_VISIBLE | \
                                      (unsigned)WS_BORDER | \
                                      (unsigned)BS_CENTER )

#define BUTTON_DISCONNECT_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                      (unsigned)WS_VISIBLE | \
                                      (unsigned)WS_BORDER | \
                                      (unsigned)BS_CENTER )

#define MAIN_WINDOW_CLIENT_CLASSNAME "MainWindowClientClass"
#define MAIN_WINDOW_CLIENT_NAME "RemoteUnixTerminal(Authorization)"

#define LABEL_LOGIN "<<< Login >>>"
#define LABEL_PASS "<<< Password >>>"
#define LABEL_COPYRIGHT "Copyright@ Magistr_Y0da"

#endif //CLIENT_MAINWINDOW_H
