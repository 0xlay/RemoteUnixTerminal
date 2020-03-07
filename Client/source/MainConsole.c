// ----------------------------------------------------------------------------
// $File: MainWindow.h $
// $Date: 02.01.2020 $
// $Revision: 23.01.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------

#include "../header/MainConsole.h"


int16_t Main_Console(HWND MainConsoleClient, const char *login, const char *password) {
    // Disable button close
    SetClassLongPtr(MainConsoleClient,
                    GCL_STYLE,
                    GetClassLongPtr(MainConsoleClient, GCL_STYLE) | CS_NOCLOSE);
    EnableMenuItem(GetSystemMenu(MainConsoleClient, FALSE),
                   SC_CLOSE,
                   MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

    if ((strcmpi(login, "") && strcmpi(password, "")) == 0) {
        MessageBoxW(NULL,
                    L"Incorrect login or password",
                    L"Error Authorization",
                    MESSAGE_BOX_ERROR_STYLE);
        return -7;
    }

    FILE *fl_logo_client_console;
    FILE *fl_settings;
    wchar_t LogoClientConsole[SIZE_LOGO_CLIENT_CONSOLE];
    char current_ip[16] = "127.0.0.1";
    char current_port[6] = "8080";

    /* Load logo*/
    fl_logo_client_console = fopen(PATH_LOGO_CLIENT_CONSOLE, "r");
    for (size_t i = 0; i < SIZE_LOGO_CLIENT_CONSOLE; ++i) {
        LogoClientConsole[i] = fgetwc(fl_logo_client_console);
        if (feof(fl_logo_client_console) != 0) { // NOLINT(hicpp-signed-bitwise)
            LogoClientConsole[i + 1] = '\0';
            break;
        }
    }
    fclose(fl_logo_client_console);

    fl_settings = fopen("../settings", "r");
    if (fl_settings != NULL) {
        fscanf(fl_settings, "%s", current_ip);
        fscanf(fl_settings, "%s", current_port);
        fclose(fl_settings);
    } else {
        MessageBoxW(NULL,
                    L"Error reading file... Default settings applied",
                    NULL,
                    MESSAGE_BOX_ERROR_STYLE);
    }


    AllocConsole();
    ShowWindow(MainConsoleClient, SW_SHOW);
    SetConsoleTitleW(MAIN_CONSOLE_CLIENT_NAME);
    system("CLS");
    wprintf(L"%s\n", LogoClientConsole);
    printf("\nCURRENT IP SERVER: %s AND PORT %s\n", current_ip, current_port);
    // TODO: Work sockets:

    WSADATA wsa_data;
    SOCKET server_socket;
    SOCKADDR_IN addr_server;

    WORD dll_ver = MAKEWORD(2, 2); // NOLINT(hicpp-signed-bitwise)
    if (WSAStartup(dll_ver, &wsa_data) != 0) {
        MessageBoxW(NULL,
                    L"Failed load WinSock dll...",
                    NULL,
                    MESSAGE_BOX_ERROR_STYLE);
        exit(WSAGetLastError());
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == server_socket) { // NOLINT(hicpp-signed-bitwise)
        MessageBoxW(NULL,
                    L"Failed created connection socket...",
                    NULL,
                    MESSAGE_BOX_ERROR_STYLE);
        //WSACleanup();
        //exit(WSAGetLastError());
        JUMP(Cleanup);
    }

    ZeroMemory(&addr_server, sizeof(addr_server));
    addr_server.sin_addr.S_un.S_addr = inet_addr(current_ip);
    addr_server.sin_port = htons(strtol(current_port, NULL, 10));
    addr_server.sin_family = AF_INET;

    if (connect(server_socket, (SOCKADDR *) &addr_server, sizeof(addr_server)) == SOCKET_ERROR) {
        MessageBoxW(NULL,
                    L"Failed connect to server...",
                    NULL,
                    MESSAGE_BOX_ERROR_STYLE);
        //WSACleanup();
        //exit(WSAGetLastError());
        JUMP(Cleanup);
    }


    char client_buff[1024];
    ssize_t len_fl = 0;
    ssize_t read_bytes = 0, write_bytes = 0;


    HANDLE hOutFile = NULL, hOutFileMapping = NULL;
    HANDLE hConsole;
    LPVOID lpMapViewOutFile = NULL;


    write_bytes = send_all(server_socket, login, strlen(login), 0);
    if (write_bytes < 0) JUMP(Cleanup);

    write_bytes = send_all(server_socket, password, strlen(password),0);
    if (write_bytes < 0) JUMP(Cleanup);

    ZeroMemory(client_buff, sizeof(client_buff));
    read_bytes = recv(server_socket, client_buff, sizeof(client_buff), 0);
    if (read_bytes < 0) JUMP(Cleanup);

    if (strcmp(client_buff, "Invalid password") == 0) JUMP(Cleanup);

    printf("[Server]: %s\n", client_buff);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (1) {
        ZeroMemory(client_buff, sizeof(client_buff));
        SetConsoleTextAttribute(hConsole, AQUA_COLOR);
        printf("Client [%s]: ", login);
        gets(client_buff);
        SetConsoleTextAttribute(hConsole, WHITE_COLOR);

        if(strcmpi(client_buff, "") == 0) {
            continue;
        }

        if (strcmpi(client_buff, "disconnect") == 0) {
            break;
        }

        if (strcmpi(client_buff, "clear") == 0) {
            system("CLS");
            continue;
        }
        // TODO: Перехватывать команду пинг и производить ёё на клиенте а не на сервере if(ping)

        if (strncmp(client_buff, "ping", 4) == 0) {
            if (strcmp(client_buff, "ping --server") == 0) {
                ZeroMemory(client_buff, sizeof(client_buff));
                memcpy(client_buff, "ping ",5);
                strcat(client_buff, current_ip);
            }
            system(client_buff);
            continue;
        }

        write_bytes = send(server_socket, client_buff, sizeof(client_buff), 0);
        if (write_bytes < 0) break;

        // Length file
        ZeroMemory(client_buff, sizeof(client_buff));
        read_bytes = recv(server_socket, client_buff, sizeof(client_buff), 0);
        if (read_bytes < 0) break;
        len_fl = atoll(client_buff); // NOLINT(cert-err34-c)

        // Created buffer
        hOutFile = CreateFile(PATH_CLIENT_OUTPUT,
                              CLIENT_OUTPUT_FILE_FLAGS,
                              0,
                              NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
        if (hOutFile == INVALID_HANDLE_VALUE) break;

        hOutFileMapping = CreateFileMapping(hOutFile,
                                            0,
                                            PAGE_READWRITE,
                                            0,
                                            len_fl,
                                            NULL);
        if (hOutFileMapping == NULL) break;

        lpMapViewOutFile = MapViewOfFile(hOutFileMapping,
                          FILE_MAP_ALL_ACCESS,
                          0,
                          0,
                          0);
        if (lpMapViewOutFile == NULL) break;

        read_bytes = recv_all(server_socket, (void*)lpMapViewOutFile, len_fl, 0);
        if (read_bytes < 0) break;
        printf("%s", (char*)lpMapViewOutFile);

        CloseHandle(hOutFile);
        CloseHandle(hOutFileMapping);
        UnmapViewOfFile(lpMapViewOutFile);
    }

    Cleanup:
    ShowWindow(MainConsoleClient, SW_HIDE);
    if (hOutFile != NULL) CloseHandle(hOutFile);
    if (hOutFileMapping != NULL) CloseHandle(hOutFileMapping);
    if (lpMapViewOutFile != NULL) UnmapViewOfFile(lpMapViewOutFile);

    closesocket(server_socket);
    WSACleanup();

    return GetLastError();
}


// ----------- Methods for working from sockets -----------
ssize_t send_all(SOCKET s, const char * buf, ssize_t len, int flags) {
    ssize_t bytes_send = 0;
    while (len) {
        buf += bytes_send;
        bytes_send = send(s, buf, len, flags);
        if (bytes_send < 0) return bytes_send;
        len -= bytes_send;
    }
    return 0;
}

ssize_t recv_all(SOCKET s, char * buf, ssize_t len, int flags) {
    ssize_t bytes_read = 0;
    while(len) {
        buf += bytes_read;
        bytes_read = recv(s, buf, len, flags);
        if (bytes_read < 0) return bytes_read;
        len -= bytes_read;
    }
    return 0;
}
// ---------------------------------------------------------
// Так же добавить поток чтобы можно было продолжать работать с клиентом дальше.