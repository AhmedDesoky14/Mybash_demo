/*     
*   Author: Ahmed Desoky
*   Date:   21/8/2023
*   Description:    Directories changer header file
*/
/*=========================================================================DEFINATIONS=================================================================================*/
#define _GNU_SOURCE
#define MAX_FILE_PATH   1000
/*==========================================================================INCLUDES===================================================================================*/
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"err_hndlr.h"
/*===========================================================================EXTERNS===================================================================================*/
/*externed global variables defined in main.c*/
extern char** command;
extern pid_t current_process_id;
extern pid_t current_process_pid;
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function Descriptions in .c file*/
int directives_parser(char*);