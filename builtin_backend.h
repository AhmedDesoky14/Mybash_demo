/*     
*   Author: Ahmed Desoky
*   Date:   16/8/2023
*   Description:    builtin backend functions header file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include<string.h>
#include<unistd.h>
#include"parser_backend.h"
#include "exec.h"
#include"err_hndlr.h"
/*===========================================================================EXTERNS===================================================================================*/
/*externed global variables defined in main.c*/
extern char** command;
extern char** history;
extern unsigned int command_args_count;
extern pid_t current_process_id;
extern pid_t current_process_pid;
extern uid_t current_user_id;
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function Descriptions in .c file*/
void echo (void);
void cd (void);
void env(void);
void type(void);
void history_print(void);