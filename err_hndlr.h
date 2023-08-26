/*     
*   Author: Ahmed Desoky
*   Date:   8/8/2023
*   Description:    Error handler header file
*/
/*=========================================================================DEFINATIONS=================================================================================*/
#define _GNU_SOURCE
#define GET_HOSTNAME_ERR    1
#define GET_USERNAME_ERR    2
#define GET_CWD_ERR         3
#define GET_COMMAND_ERR     4
#define FAILED_FORK         5
#define FAILED_OPEN_DIR     6
#define FAILED_CLOSE_DIR    7
#define FAILED_CHANGE_DIR   8
#define FAILED_CLOSE_FD     9
#define FAILED_CHANGE_FD    10

#define INITIAL_CWD_SIZE    100
/*==========================================================================INCLUDES===================================================================================*/
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/timeb.h>
#include<sys/stat.h>
#include<fcntl.h>
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
void Assign_Err(pid_t, pid_t , int);