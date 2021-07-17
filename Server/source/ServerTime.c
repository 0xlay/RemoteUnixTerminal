// ----------------------------------------------------------------------------
// $File: ServerTime.c $
// $Date: 07.02.2020 $
// $Revision: 07.02.2020 $
// $Creator: 0xlay $
// ----------------------------------------------------------------------------
#include "../header/ServerTime.h"

void system_clockf(const char * str_time_format, char * str_dest, size_t size_str_dest) {
    long int sys_time;
    struct tm * loc_time;
    char str_loc_time[100];

    sys_time = time(NULL);
    loc_time = localtime(&sys_time);

    strftime(str_loc_time, sizeof(str_loc_time), str_time_format, loc_time);

    strncpy(str_dest, str_loc_time, size_str_dest);
}