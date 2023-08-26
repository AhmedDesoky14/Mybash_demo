/*     
*   Author: Ahmed Desoky
*   Date:   8/8/2023
*   Description:    main file for the bash
*   Shell Version: 1.1.0
    Last edit: 26/8/2023
    *******************************************************************************
    * Last updates
    - history builtin command feature added
    - Redirectories fixed
*/
/*==========================================================================INCLUDES===================================================================================*/
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<unistd.h>
#include"exec.h"
#include"parser.h"
#include"builtin.h"
#include"dirctvs.h"
#include"err_hndlr.h"
/*======================================================================GLOBAL VARIABES================================================================================*/
char*  inputstring;
int check_no_input;
char** command;
unsigned int command_args_count;
char** env_variables;
unsigned int env_args_count;
char** variables;
unsigned int var_args_count;
char* exe;
char** history;
unsigned int history_num;
pid_t current_process_id;
pid_t current_process_pid;
uid_t current_user_id;
/*============================================================================MAIN=====================================================================================*/
int main(void)
{
    Shell_Init();                                   /*initiate the shell*/
    while(1)
    {
        int exe_state = 0;                         /*variable to check it to get if the command is a program to execute or not*/   
        int assign_state = 0;                      /*variable to check it to get if the command is a variable handler*/                 
        int builtin_state = 0;                     /*variable to check it to get if the command is a builtin or not*/       
        int var_ret = 0;                            /*variable to check it to get if the command is to retrieve variable or not*/ 
        Allocate_Memory();                         /*allocate memory for all global pointers*/
        Prompt();                                  /*my bash prompt*/
        check_no_input = get_command();            /*get command and tokenize it*/
        if(check_no_input == 0)                    /*check if there's no input*/
            continue;      
        /*--------------------------------*/
        builtin_state = builtin_seeker();           /*search for builtin functions*/
        if(builtin_state == 1)
        {
            break;
        }
        /*****Here*****/
        else if(builtin_state > 1)
        {
            continue;
        }
        else
        {
            /*do nothing*/
        }
        /*--------------------------------*/ 
        exe_state = exe_path();                    /*search for programs in PATH and get the exe file path*/
        /*-------------------------------*/
        assign_state = Assign_env_variables_parser();           /*search for assigning new variables or not*/
        if(assign_state == 0)
        {
            assign_state = Assign_variables_parser();
        }
        if(assign_state == 1)
        {
            continue;
        }
        else
        {
            /*do nothing*/
        }
        /*------------------------------------*/
        var_ret = var_retrieve_parser();                /*search for retrieving variables or not*/
        if(var_ret == 1)
        {
            exe_state = 1;
        }
                        //printf("EXE:%s---%d",exe,exe_state);
        /*-----------------------------------------*/
        pid_t frk_ret_pid;                          /*fork return pid*/
        if(exe_state == 1)                          /*0 means ready to execute a program*/
        {
            frk_ret_pid = fork();                   /* Forking */
        }
        else                                        /*if not executing a program, free memory and skip this iteration*/
        {
            Free_Memory();                          /*free memory*/
            continue;
        }

        if(frk_ret_pid < 0)                         /*Failed Forking*/
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_FORK); /*Assign an error to error handler*/
            Free_Memory();                          /*free memory*/
            continue;
        }
        else if(frk_ret_pid > 0)                    /*Parent process*/
        {
            int child_status = 0;
            pid_t wait_child_pid = wait(&child_status); /*wait for child process*/
            Free_Memory();                          /*free memory*/
            continue;
        }
        else if(frk_ret_pid == 0)                   /*Child process*/
        {
            int directives_state = 0;
            char** dummy_command = (char**)malloc(2*sizeof(char*)); /*initially 2, for command[0] and NULL*/
            char* command_ = (char*)malloc(COMMAND_FIRST_ARG_MAX_SIZE*sizeof(char));
            strcpy(command_,command[0]);
            dummy_command[0] = command_;
            dummy_command[1] = NULL;
            if(command_args_count > 2)
            {
                directives_state = directives_parser(command[2]);          /*file name is index 2*/
            }
            if(directives_state != 1)
            {
                int operat = execve(exe,command,env_variables); /*execute the program*/ 
            }
            else if(directives_state == 1)
            {
                int operat = execve(exe,dummy_command,env_variables); /*execute the program*/ 
            }
            printf("command not found\n");       /*command not found*/
	        return -1;
        }
    }
    Shell_Deinit();
}
