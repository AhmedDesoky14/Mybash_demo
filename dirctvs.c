/*     
*   Author: Ahmed Desoky
*   Date:   21/8/2023
*   Description:    Directories changer source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"dirctvs.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   This is the function to parse re directory
    [INPUTS]:   pointer to char for file name
    [OUTPUTS]:  NONE
    NOTES:
************************************************************************************************************************************************/
int directives_parser(char* file)
{
    int directives_state = 0;
    if(strcmp(command[1],"<<") == 0)    /*std input*/
    {
        int fd_new = open(file,O_RDONLY,0775);
        int success2 = dup2(fd_new,0);  /*file becoming standard input*/
        int success = close(fd_new);
        if(success != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_FD);
        }
        if(success2 != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CHANGE_FD);
        }
        directives_state = 1;
    }
    else if(strcmp(command[1],">") == 0) 
    {
        int fd_new = open(file,O_RDWR|O_CREAT,0775);
        int success2 = dup2(fd_new,1);  /*fie becoming standard output without append*/
        int success = close(fd_new);
        if(success != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_FD);
        }
        if(success2 != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CHANGE_FD);
        }
        directives_state = 1;
    }
    else if(strcmp(command[1],">>") == 0)
    {
        int fd_new = open(file,O_RDWR|O_CREAT|O_APPEND,0775);
        int success2 = dup2(fd_new,1);  /*fie becoming standard output with append*/
        int success = close(fd_new);
        if(success != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_FD);
        }
        if(success2 != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CHANGE_FD);
        }
        directives_state = 1;
    }
     else if(strcmp(command[1],"2>") == 0)
    {
        int fd_new = open(file,O_RDWR|O_CREAT,0775);
        int success2 = dup2(fd_new,2);  /*fie becoming standard output for errors*/
        int success = close(fd_new);
        if(success != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_FD);
        }
        if(success2 != 0)
        {
            Assign_Err(current_process_pid,current_process_id,FAILED_CHANGE_FD);
        }
        directives_state = 1;
    }
    return directives_state;
}
