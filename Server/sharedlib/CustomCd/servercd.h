// ----------------------------------------------------------------------------
// $File: servercd.h $
// $Date: 18.02.2020 $
// $Revision: 18.02.2020 $
// $Creator: Magistr_Y0da $
// ----------------------------------------------------------------------------

#ifndef SERVERCD_H
#define SERVERCD_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_PATH 4096

struct cd_settings {
  char default_path[MAX_PATH];
  char current_path[MAX_PATH];
  char prev_path[MAX_PATH];
}typedef cd_t;


extern int command_cd(const char * param, cd_t * cd);


#endif
