// ----------------------------------------------------------------------------
// $File: SettingsWindow.h $
// $Date: 05.01.2020 $
// $Revision: 05.01.2020 $
// $Creator: 0xlay $
// ----------------------------------------------------------------------------

#ifndef CLIENT_SETTINGSWINDOW_H
#define CLIENT_SETTINGSWINDOW_H

#include <windows.h>
#include <Commctrl.h>
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>

extern int SettingsWindow(HWND hwnd, HINSTANCE hInstance);
extern LRESULT ChildProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

#define MM_TO_PIXEL 3.793627
#define MAIN_SETTINGS_WINDOW_WIDTH 220
#define MAIN_SETTINGS_WINDOW_HEIGHT 280

#define EDIT_IP_CLIENT_WIDTH 150
#define EDIT_IP_CLIENT_HEIGHT 20

#define EDIT_PORT_CLIENT_WIDTH 85
#define EDIT_PORT_CLIENT_HEIGHT 20

#define BUTTON_SAVE_SETTINGS_CLIENT_WIDTH 160
#define BUTTON_SAVE_SETTINGS_CLIENT_HEIGHT 40

#define WND_SETTINGS_WINDOW_STYLE ( (unsigned)CS_HREDRAW | \
                                    (unsigned)CS_VREDRAW )

#define MAIN_SETTINGS_WINDOW_STYLE ( (unsigned)WS_OVERLAPPED | \
                                     (unsigned)WS_CAPTION | \
                                     (unsigned)WS_SYSMENU | \
                                     (unsigned)WS_MINIMIZEBOX )

#define EDIT_IP_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                  (unsigned)WS_VISIBLE | \
                                  (unsigned)WS_BORDER | \
                                  (unsigned)ES_LEFT )

#define EDIT_PORT_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                  (unsigned)WS_VISIBLE | \
                                  (unsigned)WS_BORDER | \
                                  (unsigned)ES_LEFT | \
                                  (unsigned)ES_NUMBER )

#define BUTTON_SAVE_SETTINGS_CLIENT_STYLE ( (unsigned)WS_CHILD | \
                                      (unsigned)WS_VISIBLE | \
                                      (unsigned)WS_BORDER | \
                                      (unsigned)BS_CENTER )

#define MAIN_SETTINGS_WINDOW_CLASSNAME "SettingsWindowClass"
#define MAIN_SETTINGS_WINDOW_NAME "Settings"
#define LABEL_IP "IP Address"
#define LABEL_PORT "Port"

#define PATH_SETTINGS "../data/settings"

#endif //CLIENT_SETTINGSWINDOW_H
