/*     
*   Author: Ahmed Desoky
*   Date:   16/8/2023
*   Description:    builtin functions source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"builtin.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   This is the main function in builtin.c used to operate all builtin commands
    [INPUTS]:   NONE
    [OUTPUTS]:  integer, indicating which command is performed
    NOTES:  This function uses all functions of builtin_backend files
************************************************************************************************************************************************/
int builtin_seeker(void)
{
    int builtin_state = 0;
    //cd whichis type echo exit 
    if(strcmp(command[0],"exit") == 0)
    {
        builtin_state = 1;
    }
    else if(strcmp(command[0],"echo") == 0)
    {
        echo();
        builtin_state = 2;
    }
    else if(strcmp(command[0],"type") == 0)
    {
        if(strcmp(command[1],"echo") == 0)
        {
            printf("%s is a shell builtin\n",command[1]);
        }
        else if(strcmp(command[1],"type") == 0)
        {
            printf("%s is a shell builtin\n",command[1]);
        }
        else if(strcmp(command[1],"cd") == 0)
        {
            printf("%s is a shell builtin\n",command[1]);
        }
        else if(strcmp(command[1],"env") == 0)
        {
            printf("%s is a shell builtin\n",command[1]);
        }
        else if(strcmp(command[1],"history") == 0)
        {
            printf("%s is a shell builtin\n",command[1]);
        }
        else
        {
           type();
        }
        builtin_state = 3;
    } 
    else if(strcmp(command[0],"cd") == 0)
    {
        cd();
        builtin_state = 4;
    }
    else if(strcmp(command[0],"env") == 0)
    {
        env();
        builtin_state=  5;
    }
    else if(strcmp(command[0],"history") == 0)
    {
        history_print();
        builtin_state=  6;
    }
    else
    {
        builtin_state = 0;
    }
    return builtin_state;
}