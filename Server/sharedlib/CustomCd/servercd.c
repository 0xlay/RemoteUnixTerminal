// ----------------------------------------------------------------------------
// $File: servercd.c $
// $Date: 18.02.2020 $
// $Revision: 18.02.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------


#include "servercd.h"

int command_cd(const char *  param, cd_t * cd) {
    int ret_val;
    getcwd(cd->current_path, MAX_PATH);

    if ( (strcmp(param, "cd --") == 0) || \
         (strcmp(param, "cd ~") == 0)  || \
         (strcmp(param, "cd ~/") == 0) ) {
        
        ret_val = chdir(cd->default_path);
        if (ret_val < 0) {
            return errno;
        }
        memcpy(cd->prev_path, cd->current_path, MAX_PATH);
        return 0;
    }

    if ( (strcmp(param, "cd -") == 0) || (strcmp(param, "cd") == 0) ) {
        ret_val = chdir(cd->prev_path);
        if (ret_val < 0) {
            return errno;
        }
        memcpy(cd->prev_path, cd->current_path, MAX_PATH);
        return 0;
    }

    if ( ( strncmp(param, "cd /", 4) == 0) || (strncmp(param, "cd ", 3) ) == 0) {
        int i, j;
        memcpy(cd->prev_path, cd->current_path, MAX_PATH); 
        for (i = 0, j = 3; param[j] != '\0'; ++i, ++j) {
            cd->current_path[i] = param[j];
        }
        
        cd->current_path[i] = '\0';
        
        ret_val = chdir(cd->current_path);
        if (ret_val < 0) {
           return errno; 
        }
        return 0;
    }

    return 2;
}
