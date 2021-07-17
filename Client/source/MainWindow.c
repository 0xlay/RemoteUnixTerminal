// ----------------------------------------------------------------------------
// $File: MainWindow.c $
// $Date: 30.12.2019 $
// $Revision: 05.01.2020 $
// $Creator: 0xlay $
// ----------------------------------------------------------------------------

#include "../header/MainConsole.h"
#include "../header/MainWindow.h"
#include "../header/SettingsWindow.h"
#include "../resources/Resources.h"

static HDC hdc_WndProc;
static PAINTSTRUCT paint_struct;
static HWND edit_login;
static HWND edit_password;
static HWND button_settings;
static HWND button_connect;
static HWND MainWindowClient;
static HWND MainConsoleClient;
static HINSTANCE Main_Instance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    HDC hdc;
    MSG msg;
    WNDCLASSEX wnd_MainWindowClient;
    RECT rect_MainWindowClient;
    Main_Instance = hInstance;
    

    memset(&wnd_MainWindowClient, 0, sizeof(WNDCLASSEX));
    wnd_MainWindowClient.cbSize = sizeof(WNDCLASSEX);
    wnd_MainWindowClient.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd_MainWindowClient.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON32), IMAGE_ICON, 32, 32, 0);
    wnd_MainWindowClient.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON16), IMAGE_ICON, 16, 16, 0);
    wnd_MainWindowClient.style = WND_MAIN_WINDOW_CLIENT_STYLE;
    wnd_MainWindowClient.lpfnWndProc = (WNDPROC)WndProc;
    wnd_MainWindowClient.hInstance = hInstance;
    wnd_MainWindowClient.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wnd_MainWindowClient.lpszClassName = MAIN_WINDOW_CLIENT_CLASSNAME;
    if ( !RegisterClassEx(&wnd_MainWindowClient) ) {
        return EXIT_FAILURE;
    }


    MainWindowClient = CreateWindow(MAIN_WINDOW_CLIENT_CLASSNAME,
                                    MAIN_WINDOW_CLIENT_NAME,
                                    MAIN_WINDOW_CLIENT_STYLE,
                                    0,
                                    0,
                                    MAIN_WINDOW_CLIENT_WIDTH,
                                    MAIN_WINDOW_CLIENT_HEIGHT,
                                    NULL,
                                    NULL,
                                    wnd_MainWindowClient.hInstance,
                                    NULL);
    if (MainWindowClient == INVALID_HANDLE_VALUE) {
        return EXIT_FAILURE;
    }
                /* Move window to center screen */
    hdc = GetDC(NULL);
    uint16_t h_size = GetDeviceCaps(hdc, HORZSIZE) * MM_TO_PIXEL;
    uint16_t v_size = GetDeviceCaps(hdc, VERTSIZE) * MM_TO_PIXEL;
    ReleaseDC(MainWindowClient,hdc);

    GetWindowRect(MainWindowClient, &rect_MainWindowClient);
    uint16_t x_pos = rect_MainWindowClient.right  - rect_MainWindowClient.left;
    uint16_t y_pos = rect_MainWindowClient.bottom - rect_MainWindowClient.top;

    MoveWindow(MainWindowClient,
                (h_size - x_pos) / 2,
                (v_size - y_pos) / 2,
                MAIN_WINDOW_CLIENT_WIDTH,
                MAIN_WINDOW_CLIENT_HEIGHT,
                TRUE);


            /* Hide console */
    MainConsoleClient = GetConsoleWindow();
    ShowWindow(MainConsoleClient, SW_HIDE);


      /* Show and update  main window */
    ShowWindow(MainWindowClient, nCmdShow);
    UpdateWindow(MainWindowClient);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterClass(MAIN_WINDOW_CLIENT_CLASSNAME, hInstance);
    return msg.wParam;
}


LRESULT WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
    switch (uMessage)
    {
        case WM_DESTROY:
            DeleteDC(hdc_WndProc);
            PostQuitMessage(EXIT_SUCCESS);
            break;

        case WM_PAINT:
            hdc_WndProc = BeginPaint(hwnd, &paint_struct);

            TextOutW(hdc_WndProc,
                    (MAIN_WINDOW_CLIENT_WIDTH / 2.0) - (wcslen(LABEL_LOGIN) * 4), 60,
                    LABEL_LOGIN, wcslen(LABEL_LOGIN));
            TextOutW(hdc_WndProc,
                    (MAIN_WINDOW_CLIENT_WIDTH / 2.0) - (wcslen(LABEL_PASS) * 4), 110,
                    LABEL_PASS, wcslen(LABEL_PASS));
            EndPaint(hwnd, &paint_struct);
            break;

        case WM_CREATE:
            edit_login = CreateWindow("EDIT",
                                      "",
                                      EDIT_LOGIN_CLIENT_STYLE,
                                      65,
                                      80,
                                      EDIT_LOGIN_CLIENT_WIDTH,
                                      EDIT_LOGIN_CLIENT_HEIGHT,
                                      hwnd,
                                      NULL,
                                      ((LPCREATESTRUCT)lParam)->hInstance,
                                      NULL);
            if (edit_login == INVALID_HANDLE_VALUE) { return EXIT_FAILURE; }
            ShowWindow(edit_login, SW_SHOWNORMAL);

            edit_password = CreateWindow("EDIT",
                                      "",
                                      EDIT_PASSWORD_CLIENT_STYLE,
                                      65,
                                      130,
                                      EDIT_PASSWORD_CLIENT_WIDTH,
                                      EDIT_PASSWORD_CLIENT_HEIGHT,
                                      hwnd,
                                      NULL,
                                      ((LPCREATESTRUCT)lParam)->hInstance,
                                      NULL);
            if (edit_password == INVALID_HANDLE_VALUE) { return EXIT_FAILURE; }
            ShowWindow(edit_password, SW_SHOWNORMAL);

            button_settings = CreateWindow("BUTTON",
                                          "Settings",
                                           BUTTON_SETTINGS_CLIENT_STYLE,
                                           65,
                                           160,
                                           BUTTON_SETTINGS_CLIENT_WIDTH,
                                           BUTTON_SETTINGS_CLIENT_HEIGHT,
                                           hwnd,
                                           NULL,
                                           ((LPCREATESTRUCT)lParam)->hInstance,
                                           NULL);
            if (button_settings == INVALID_HANDLE_VALUE) { return EXIT_FAILURE; }
            ShowWindow(button_settings, SW_SHOWNORMAL);

            button_connect = CreateWindow("BUTTON",
                                          "Connect",
                                          BUTTON_CONNECT_CLIENT_STYLE,
                                          65,
                                          210,
                                          BUTTON_CONNECT_CLIENT_WIDTH,
                                          BUTTON_CONNECT_CLIENT_HEIGHT,
                                          hwnd,
                                          NULL,
                                          ((LPCREATESTRUCT)lParam)->hInstance,
                                          NULL);
            if (button_connect == INVALID_HANDLE_VALUE) { return EXIT_FAILURE; }
            ShowWindow(button_connect, SW_SHOWNORMAL);
            break;

        case WM_COMMAND:
            if (lParam == (LPARAM)button_settings) {
                EnableWindow(button_settings, FALSE);
                EnableWindow(button_connect, FALSE);

                SettingsWindow(hwnd, Main_Instance);

                EnableWindow(button_settings, TRUE);
                EnableWindow(button_connect, TRUE);
            }
            if (lParam == (LPARAM)button_connect) {
                EnableWindow(button_connect, FALSE);
                EnableWindow(button_settings, FALSE);
                ShowWindow(MainWindowClient, SW_MINIMIZE);

                char login[50];
                char password[50];
                GetWindowTextA(edit_login, login, 50);
                GetWindowTextA(edit_password, password, 50);

                ShowWindow(MainWindowClient, SW_HIDE);
                Main_Console(MainConsoleClient, login, password);
                
                ShowWindow(MainWindowClient, SW_SHOWNORMAL);
                EnableWindow(button_connect, TRUE);
                EnableWindow(button_settings, TRUE);
            }
            break;

        default:
            return DefWindowProc(hwnd, uMessage, wParam, lParam);
    }
    return EXIT_SUCCESS;
}
