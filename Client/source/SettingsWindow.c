// ----------------------------------------------------------------------------
// $File: SettingsWindow.c $
// $Date: 05.01.2020 $
// $Revision: 05.01.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------

#include "../header/SettingsWindow.h"

static HWND edit_ip;
static HWND edit_port;
static HWND button_save_settings;
static HDC hdc_ChildProc;
static PAINTSTRUCT paint_struct;

int SettingsWindow(HWND hwnd, HINSTANCE hInstance) {
    WNDCLASSEX wnd_SettingsWindow;
    HWND SettingsWindow;
    MSG msg;
    HDC hdc;
    RECT rect_SettingsWindow;

    memset(&wnd_SettingsWindow, 0, sizeof(WNDCLASSEX));
    wnd_SettingsWindow.cbSize = sizeof(WNDCLASSEX);
    wnd_SettingsWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd_SettingsWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wnd_SettingsWindow.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wnd_SettingsWindow.style = WND_SETTINGS_WINDOW_STYLE;
    wnd_SettingsWindow.lpfnWndProc = (WNDPROC)ChildProc;
    wnd_SettingsWindow.hInstance = hInstance;
    wnd_SettingsWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wnd_SettingsWindow.lpszClassName = MAIN_SETTINGS_WINDOW_CLASSNAME;

    if ( !RegisterClassEx(&wnd_SettingsWindow) ) {
        exit(GetLastError());
    }

    SettingsWindow = CreateWindow(MAIN_SETTINGS_WINDOW_CLASSNAME,
                               MAIN_SETTINGS_WINDOW_NAME,
                               MAIN_SETTINGS_WINDOW_STYLE,
                               0,
                               0,
                               MAIN_SETTINGS_WINDOW_WIDTH,
                               MAIN_SETTINGS_WINDOW_HEIGHT,
                               NULL,
                               NULL,
                               wnd_SettingsWindow.hInstance,
                               NULL);

    if (SettingsWindow == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }

    /* Move window to center screen */
    hdc = GetDC(NULL);
    uint16_t h_size = GetDeviceCaps(hdc, HORZSIZE) * MM_TO_PIXEL;
    uint16_t v_size = GetDeviceCaps(hdc, VERTSIZE) * MM_TO_PIXEL;
    ReleaseDC(SettingsWindow, hdc);

    GetWindowRect(SettingsWindow, &rect_SettingsWindow);
    uint16_t x_pos = rect_SettingsWindow.right  - rect_SettingsWindow.left;
    uint16_t y_pos = rect_SettingsWindow.bottom - rect_SettingsWindow.top;

    MoveWindow(SettingsWindow,
               (h_size - x_pos) / 2,
               (v_size - y_pos) / 2,
               MAIN_SETTINGS_WINDOW_WIDTH,
               MAIN_SETTINGS_WINDOW_HEIGHT,
               TRUE);

    ShowWindow(hwnd, SW_HIDE);

    ShowWindow(SettingsWindow, SW_NORMAL);
    UpdateWindow(SettingsWindow);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterClass(MAIN_SETTINGS_WINDOW_CLASSNAME, hInstance);
    ShowWindow(hwnd, SW_NORMAL);

    return msg.wParam;
}

LRESULT ChildProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
    switch (uMessage)
    {
        case WM_DESTROY:
            DeleteDC(hdc_ChildProc);
            PostQuitMessage(EXIT_SUCCESS);
            break;

        case WM_PAINT:
            hdc_ChildProc = BeginPaint(hwnd, &paint_struct);

            TextOut(hdc_ChildProc,
                    75, 100,
                    LABEL_IP, sizeof(LABEL_IP));

            TextOut(hdc_ChildProc,
                    95, 145,
                    LABEL_PORT, sizeof(LABEL_PORT));

            EndPaint(hwnd, &paint_struct);
            break;

        case WM_CREATE:
            edit_ip = CreateWindow(WC_IPADDRESS,
                                      "",
                                      EDIT_IP_CLIENT_STYLE,
                                      30,
                                      120,
                                      EDIT_IP_CLIENT_WIDTH,
                                      EDIT_IP_CLIENT_HEIGHT,
                                      hwnd,
                                      NULL,
                                      ((LPCREATESTRUCT)lParam)->hInstance,
                                      NULL);
            if (edit_ip == INVALID_HANDLE_VALUE) { return EXIT_FAILURE; }
            ShowWindow(edit_ip, SW_SHOWNORMAL);

            edit_port = CreateWindow("EDIT",
                                     "",
                                     EDIT_PORT_CLIENT_STYLE,
                                     65,
                                     165,
                                     EDIT_PORT_CLIENT_WIDTH,
                                     EDIT_PORT_CLIENT_HEIGHT,
                                     hwnd,
                                     NULL,
                                     ((LPCREATESTRUCT)lParam)->hInstance,
                                     NULL);
            if (edit_port == INVALID_HANDLE_VALUE) { return EXIT_FAILURE; }
            ShowWindow(edit_port, SW_SHOWNORMAL);

            button_save_settings = CreateWindow("BUTTON",
                                                "save",
                                                BUTTON_SAVE_SETTINGS_CLIENT_STYLE,
                                                25,
                                                200,
                                                BUTTON_SAVE_SETTINGS_CLIENT_WIDTH,
                                                BUTTON_SAVE_SETTINGS_CLIENT_HEIGHT,
                                                hwnd,
                                                NULL,
                                                ((LPCREATESTRUCT)lParam)->hInstance,
                                                NULL);
            if (button_save_settings == INVALID_HANDLE_VALUE) { return EXIT_FAILURE; }
            ShowWindow(edit_port, SW_SHOWNORMAL);
            break;

        case WM_COMMAND:
            if (lParam == (LPARAM)button_save_settings) {
                // save settings to file
                char new_ip[16];
                char new_port[6];

                GetWindowTextA(edit_ip, new_ip, 16);
                GetWindowTextA(edit_port, new_port, 6);
                FILE *fl_settings = fopen(PATH_SETTINGS, "w");
                fprintf(fl_settings, "%s\n", new_ip);
                fprintf(fl_settings, "%s\n", new_port);
                fclose(fl_settings);
            }
            break;

        default:
            return DefWindowProc(hwnd, uMessage, wParam, lParam);
    }
    return EXIT_SUCCESS;
}