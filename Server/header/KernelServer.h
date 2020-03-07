// ----------------------------------------------------------------------------
// $File: KernelServer.h $
// $Date: 20.01.2020 $
// $Revision: 03.03.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------


#ifndef KERNEL_SERVER_H
#define KERNEL_SERVER_H

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close(), read(), write() */
#include <fcntl.h>      /* for open() */
#include <errno.h>
#include <wchar.h>
#include <sys/mman.h>   /* map file */
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

#include "../header/ServerTime.h"
#include "../sharedlib/CustomCd/servercd.h"

extern ssize_t write_log(int fl, int count_str,...);
extern ssize_t send_str(int fd, const char * msg, int flags);
extern ssize_t send_data(int fd, const char * data, int flags);
extern ssize_t fread_str(int fl, char * buff, int size_buff);
extern char * str_tolower(char *str);

#define SERV_OUTPUT "/data/server_output"
#define SERV_AUTHORIZATION "/data/authorization.txt"

#define JUMP( name_label ) \
            goto name_label

#endif
