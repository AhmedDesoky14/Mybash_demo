/*     
*   Author: Ahmed Desoky
*   Date:   8/8/2023
*   Description:    Error handler source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"err_hndlr.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
void Assign_Err(pid_t ppid, pid_t pid, int err_type)
{
    char ppid_str[6], pid_str[6], err_type_str[6],Err_str[100]="\n-->"; /*max number of processes is 32768*/
    sprintf(ppid_str,"%d",ppid);
    sprintf(pid_str,"%d",pid);
    sprintf(err_type_str,"%d",err_type);
    strcat(Err_str,ppid_str);
    strcat(Err_str,":");
    strcat(Err_str,pid_str);
    strcat(Err_str,":");
    strcat(Err_str,err_type_str);
    strcat(Err_str,":");
    /*This switch block is resizable due to number of possible errors*/
    switch(err_type)
    {  
        case 1:
            strcat(Err_str,"GET_HOSTNAME_ERR");
            break;
        case 2:
            strcat(Err_str,"GET_USERNAME_ERR");
            break;
        case 3:
            strcat(Err_str,"GET_CWD_ERR");
            break;
        case 4:
            strcat(Err_str,"GET_COMMAND_ERR");
            break;
        case 5:
            strcat(Err_str,"FAILED_FORK");
            break;
        case 6:
            strcat(Err_str,"FAILED_OPEN_DIR");
            break;
        case 7:
            strcat(Err_str,"FAILED_CLOSE_DIR");
            break;
    }  
    int fd_err = open("./Err_Hist.txt", O_RDWR|O_APPEND|O_CREAT,0775);
    if(fd_err < 0)
    {
        printf("Error Handler Fault - Failed to open errors record file");
    }
    int Err_write = write(fd_err,Err_str,40);
    if(Err_write < 0)
    {
        printf("Error Handler Fault - Failed to write to errors record file");
    }
    int close_check = close(fd_err);
    if(close_check != 0)
    {
        printf("Error Handler Fault - Failed to close errors record file");
    }
}

