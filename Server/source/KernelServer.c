// ----------------------------------------------------------------------------
// $File: KernelServer.c $
// $Date: 20.01.2020 $
// $Revision: 20.03.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------
#include "../header/KernelServer.h"

int main(int argc, char** argv) {
    struct sockaddr_in addr_server;
    struct sockaddr_in addr_client;
    int listener_socket, connection_socket;
    int size_addr_client = sizeof(addr_client);
    int64_t bytes_read = 0, bytes_write = 0;
    int status_command = 0;

    char login[50];
    char password[50];
    
    bool valid_login = false;
    bool valid_password = false;

    char PATH_CUSTOM_OUTPUT[MAX_PATH];
    char PATH_AUTHORIZATION[MAX_PATH];
    
    getcwd(PATH_CUSTOM_OUTPUT, sizeof(PATH_CUSTOM_OUTPUT));
    getcwd(PATH_AUTHORIZATION, sizeof(PATH_AUTHORIZATION));

    strcat(PATH_CUSTOM_OUTPUT, SERV_OUTPUT);
    strcat(PATH_AUTHORIZATION, SERV_AUTHORIZATION);

    char str_time[100];

    int log_file;
    int out_file;
    int authorization_file;

    char buffer[1024];
    struct stat info_file;
    void * file_memory;
    cd_t cd;
    system_clockf("log/%H-%M-%S_%d.%m.%Y.txt", str_time, sizeof(str_time));

    // Server - log file
    log_file = open(str_time, 
                    O_CREAT | O_WRONLY, 
                    S_IRUSR | S_IWUSR | \
                    S_IRGRP | S_IROTH | \
                    __S_IFREG);
    if (log_file < 0) {
        exit(errno);
    }

    // Server - stdout file
    out_file = open(PATH_CUSTOM_OUTPUT, 
                    O_CREAT | O_RDONLY, 
                    S_IRUSR | S_IWUSR | \
                    S_IRGRP | S_IROTH | \
                    __S_IFREG);
    if (out_file < 0) {
        close(log_file);
        exit(errno);
    }


    // Server - file for save login and password
    authorization_file = open(PATH_AUTHORIZATION,
                                O_CREAT | O_RDONLY,
                                S_IRUSR | S_IWUSR | \
                                __S_IFREG);
    if (authorization_file < 0) {
        write_log(log_file, 1, \
        "[Server]=> Authorization file (/data/authorization.txt) not found...");
        close(log_file);
        close(out_file);
        exit(errno);
    }

    bytes_read = fread_str(authorization_file, login, sizeof(login));
    if (bytes_read < 0) {
        write_log(log_file, 1,
        "[Server]=> Failed read [login] from authoriazation file...");
        close(log_file);
        close(out_file);
        close(authorization_file);
        exit(errno);
    }

    bytes_read = fread_str(authorization_file, password, sizeof(password));
    if (bytes_read < 0) {
        write_log(log_file, 1,
        "[Server]=> Failed read [password] from authoriazation file...");
        close(log_file);
        close(out_file);
        close(authorization_file);
        exit(errno);
    }
    close(authorization_file);



    listener_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_socket < 0) {
        write_log(log_file, 2, 
        "[Server]=> Failed create socket: ", strerror(errno));
        JUMP(ServerClean);
    }

    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_server.sin_port = htons(65322);
    addr_server.sin_family = AF_INET;

    if (bind(listener_socket, 
        (struct sockaddr *)&addr_server, 
        sizeof(addr_server)) < 0) {
        write_log(log_file, 2, 
        "[Server]=> Failed bind socket: ", strerror(errno));
        JUMP(ServerClean);
    } 

    listen(listener_socket, SOMAXCONN);
    connection_socket = accept(listener_socket, 
                              (struct sockaddr *)&addr_client, 
                              &size_addr_client);
    if (connection_socket < 0) {
        write_log(log_file, 2, 
        "[Server]=> Failed accept socket: ", strerror(errno));
        JUMP(ServerClean);
    }



    memset(buffer, 0, sizeof(buffer));
    bytes_read = recv(connection_socket, buffer, sizeof(buffer), 0);
    if (bytes_read < 0) {
        write_log(log_file, 2, 
        "[Server]=> Failed read message(Login): ", strerror(errno));
        JUMP(ServerClean);
    }
    if (strcmp(login, buffer) == 0) valid_login = true;


    memset(buffer, 0, sizeof(buffer));
    bytes_read  = recv(connection_socket, buffer, sizeof(buffer), 0);
    if (bytes_read < 0) {
        write_log(log_file, 2, 
        "[Server]=> Failed read message(Password): ", strerror(errno));
        JUMP(ServerClean);
    }
    if (strcmp(password, buffer) == 0) valid_password = true;



    if ( !(valid_login && valid_password) )  {
        send_str(connection_socket, "Invalid password", 0);
        write_log(log_file, 1, 
        "[Server]=> Client failed connected to server... (Invalid password or login)");
        JUMP(ServerClean);
    }

    bytes_write = write_log(log_file, 1, 
    "[Server]=> Client connected successfully...\n");
    if (bytes_write < 0) {
        JUMP(ServerClean);
    }
    
    bytes_write = send_str(connection_socket, "Server connected successfully...", 0);
    if (bytes_write < 0) {
        write_log(log_file, 2, 
        "[Server]=> Failed send message:", strerror(errno));
        JUMP(ServerClean);
    }

    // Default Directory
    strcpy(cd.default_path, getenv("HOME"));
    chdir(cd.default_path);
    
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        system_clockf("[%H:%M:%S]", str_time, sizeof(str_time));
        
        
        bytes_read = recv(connection_socket, buffer, sizeof(buffer), 0);
        if (bytes_read <= 0) {
            write_log(log_file, 2, 
            "[Server]=> Failed read message: ", strerror(errno));
            break;
        }
        
        bytes_write = write_log(log_file, 4, str_time, "<->[Client]=> ", buffer, "\n");
        if (bytes_write < 0) {
            break;
        }
                
        if ( strcasecmp(buffer, "help") == 0 ) {
            bytes_write = send_data(connection_socket, 
            "close-server - (command for off server)\
            \ndisconnect - (command for disconnect client)\n", 0);
            if (bytes_write < 0) {
                write_log(log_file, 2, 
                "[Server]=> Failed send message: ", strerror(errno));
                break;
            }
            continue;
        }

        if ( strncmp(buffer, "cd", 2) == 0) {
            status_command = command_cd(buffer, &cd); // share func libCD.so
            if (status_command != 0) {
                bytes_write = send_data(connection_socket, 
                                        "[Server]=> Command not found...\n", 0);
                if (bytes_write < 0) {
                    write_log(log_file, 2, 
                    "[Server]=> Failed send message: ", strerror(errno));
                    break;
                }
                continue;
            }

            char * path_buffer = malloc(MAX_PATH + 1);
            getcwd(path_buffer, MAX_PATH + 1);

            bytes_write = send_data(connection_socket, strcat(path_buffer, "\n"), 0);
            if (bytes_write < 0) {
                write_log(log_file, 2, 
                "[Server]=> Failed send message: ", strerror(errno));
                free(path_buffer);
                break;
            }

            free(path_buffer);
            continue;
        }

        status_command = system(strcat(strcat(buffer, ">"), 
                                PATH_CUSTOM_OUTPUT));
        if (status_command == 32512) {
            bytes_write = send_data(connection_socket, 
                                    "[Server]=> Command not found...\n", 0);
            if (bytes_write < 0 ) {
                write_log(log_file, 2, 
                "[Server]=> Failed send message: ", strerror(errno));
                break;
            }
            bytes_write = write_log(log_file, 1, 
            "[Server]=> Command not found...\n");
            if (bytes_write < 0) {
                break;
            }
            continue;
        }

        fstat(out_file, &info_file);
        if ((size_t)info_file.st_size == 0) {
            bytes_write = send_data(connection_socket, 
                                    "Successfully completed...\n", 0);
            if (bytes_write < 0 ) {
                write_log(log_file, 2, 
                "[Server]=> Failed send message: ", strerror(errno));
                break;
            }
            continue;
        }
        //
        file_memory =  mmap(0, 
                            (size_t)info_file.st_size, 
                            PROT_READ, MAP_SHARED, 
                            out_file, 0);
        if (file_memory == MAP_FAILED) {
            write_log(log_file, 2,
            "[Server]=> Failed mapping file: ", strerror(errno));
            break;
        }
        

        bytes_write = send_data(connection_socket, (char *)file_memory, 0);
        if (bytes_write < 0 ) {
            write_log(log_file, 2, 
            "[Server]=> Failed send message: ", strerror(errno));
            break;
        }    
        munmap(file_memory, info_file.st_size);
    }

    ServerClean:
    remove(PATH_CUSTOM_OUTPUT);
    if (log_file != 0) close(log_file);
    if (out_file != 0) close(out_file);
    if (listener_socket != 0) close(listener_socket);
    if (connection_socket != 0) close(connection_socket);
    return errno;
}

// writer log server
ssize_t write_log(int fl, int count_str,...) {
    ssize_t write_bytes = 0;
    char* buff;
    va_list args;
    va_start(args, count_str);
    for (;count_str > 0;count_str--) {
        buff = va_arg(args, char*);
        write_bytes = write(fl, buff, strlen(buff) * sizeof(char));
        if (write_bytes < 0) break;
    }
    va_end(args);
    return write_bytes;
}

ssize_t fread_str(int fl, char * buff, int size_buff) {
    char chr;
    while (size_buff) {
        if (read(fl, &chr, 1) < 0) return -1;
        if (chr == '\n') {
            *buff = '\0';
            break;
        }
        *buff = chr;
        ++buff;
        --size_buff;
    }
    return 0;
}

ssize_t send_str(int fd, const char * msg, int flags) {
    return send(fd, msg, strlen(msg), flags);
}

ssize_t send_data(int fd, const char * data, int flags) {
    char buff[33];
    ssize_t bytes_write;
    ssize_t len_msg;
    sprintf(buff, "%ld", strlen(data));

    len_msg = strlen(buff);
    while(len_msg) {
        bytes_write = send(fd, buff, strlen(buff), flags);
        if (bytes_write < 0 ) return bytes_write; 
        len_msg -= bytes_write;
    }

    len_msg = strlen(data);
    while(len_msg) {
        bytes_write = send(fd, data, strlen(data), flags);
        if (bytes_write < 0 ) return bytes_write;
        len_msg -= bytes_write;
    }
    return 0;
}

char * str_tolower(char *str) {
    for(int i = 0; str[i] != '\0'; ++i) {
        str[i] = tolower(str[i]);
    }    
    return str;
}
