//
// Created by Mojes on 08.02.2020.
//

#ifndef CLIENT_RESOURCES_H
#define CLIENT_RESOURCES_H

#define IDI_MAIN_ICON32 1
#define IDI_MAIN_ICON16 2

#define VER_FILE                        1,0,0,0
#define VER_FILE_STR                    "1.0.0.0\0"

#define VER_PRODUCT                     1,0,0,0
#define VER_PRODUCT_STR                 "1.0\0"

#define PRODUCT_NAME_STR                 "RemoteUnixTerminal"
#define COMPANY_NAME_STR                 "Magistr_Y0da"
#define ORIGINAL_FILENAME_STR            "Client_RemoteUnixTerminal"
#define DESCRIPTION_STR                  "Linux terminal remote access application"

#ifndef PRERELEASE
#define VER_PRERELEASE                   1
#else
#define VER_PRERELEASE                   VS_FF_PRERELEASE
#endif

#endif //CLIENT_RESOURCES_H
