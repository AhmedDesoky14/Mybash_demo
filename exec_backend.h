/*     
*   Author: Ahmed Desoky
*   Date:   8/8/2023
*   Description:    bash backend functions header file
*/
/*=========================================================================DEFINATIONS=================================================================================*/
#define _GNU_SOURCE
#define HOST_NAME_INITIAL_SIZE       100
#define USER_NAME_INITIAL_SIZE       100
#define CWD_INITIAL_SIZE             1000
#define INPUT_MAX_SIZE               10000
#define COMMAND_MAX_SIZE             1000
#define COMMAND_FIRST_ARG_MAX_SIZE   100
#define VAR_ARGS_MAX                 10000
#define PATH_VAR_MAX_SIZE            10000
/*==========================================================================INCLUDES===================================================================================*/
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include"err_hndlr.h"
/*===========================================================================EXTERNS===================================================================================*/
/*externed global variables defined in main.c*/
extern char*  inputstring;
extern int check_no_input;
extern char** command;
extern unsigned int command_args_count;
extern char** env_variables;
extern unsigned int env_args_count;
extern char** variables;
extern unsigned int var_args_count;
extern char* exe;
extern char** history;
extern unsigned int history_num;
extern pid_t current_process_id;
extern pid_t current_process_pid;
extern uid_t current_user_id;
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
extern char** environ;  /*environ extern*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*externs from exec_backend.c file to be included in another places*/
extern char* host_name;
extern char* user_name;
extern char* cwd;
extern unsigned int host_name_size;
extern unsigned int user_name_size;
extern unsigned int cwd_size;
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function Descriptions in .c file*/
void get_status(void);
void get_PATH_var(char* PATH_var);
unsigned int count_paths(char*);
void Exec_Paths_tokenizer(char*,char**);
int Exec_Seeker(char*);
int special_path_seeker(char*);