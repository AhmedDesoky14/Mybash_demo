/*     
*   Author: Ahmed Desoky
*   Date:   8/8/2023
*   Description:    pasrer backend functions header file
*/
/*=========================================================================DEFINATIONS=================================================================================*/
#define Varibales_Tokens    4
#define VAR_MAX_SIZE        10000
/*==========================================================================INCLUDES===================================================================================*/
#include<stddef.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
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
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*externed global variables defined in exec_backend.c*/
extern char* cwd;
extern unsigned int cwd_size;
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function Descriptions in .c file*/
int search_in_env(char*,char*);
int search_in_env_for_location(char*,int*);
int search_in_local(char*,char*);
int search_in_local_for_location(char*,int*);
void remove_char(char*,char);