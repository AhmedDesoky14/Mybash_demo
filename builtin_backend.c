/*     
*   Author: Ahmed Desoky
*   Date:   16/8/2023
*   Description:    builtin backend functions source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"builtin_backend.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from builtin.c to perform echo command 
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: This function uses, search_in_env, search_in_local functions from parser_backend files
************************************************************************************************************************************************/
void echo (void)
{
    for(unsigned int i=1 ; command[i] != NULL ; i++)
    {
        char var_arr[VAR_MAX_SIZE] = ""; /*allocate statically certain array*/
        if(command[i][0] == '$')
        {
            remove_char(command[i],'$');
            int found = search_in_env(command[i],var_arr);
            if(found == 1)
            {
                for(unsigned int l=0 ; var_arr[l] != '\0' ; l++)
                {
                    if(var_arr[l] == '=')
                    {
                        printf("%s ",var_arr+l+1);
                        break;
                    }
                }
                continue;
            }
            else
            {
                int found = search_in_local(command[i],var_arr);
                if(found == 1)
                {

                    for(unsigned int l=0 ; var_arr[l] != '\0' ; l++)
                    {
                        if(var_arr[l] == '=')
                        {
                            printf("%s ",var_arr+l+1);
                            break;
                        }
                    }
                    continue;
                }
                else
                {
                    /*do nothing*/
                }
            }
        }
        else
        {
            char* print_ptr = command[i];
            printf("%s ",print_ptr);
        }
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from builtin.c to perform type command 
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES:  This function uses, get_PATH_var, count_paths, Exec_Paths_tokenizer, special_path_seeker functions from exec_backend files
************************************************************************************************************************************************/
void type(void)
{
    int command_match = 0;
    char PATH_var[PATH_VAR_MAX_SIZE];
    get_PATH_var(PATH_var);
    unsigned int Paths_count = count_paths(PATH_var);
    char** Type_Paths = (char**)malloc((Paths_count+1)*sizeof(char*));
    Exec_Paths_tokenizer(PATH_var,Type_Paths);
    for(unsigned int n=0 ; n<Paths_count ; n++)
    {
        command_match = special_path_seeker(Type_Paths[n]);
        if(command_match == 1)
            break;
    }
    free(Type_Paths);
    if(command_match == 1)
    {
        printf("%s is %s\n",command[1],exe);    /*command[1] for the second argument of command which its type to be found*/
    }
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from builtin.c to perform change directory (cd) command 
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES:  This function assigns its errors to err_hndlr files
************************************************************************************************************************************************/
void cd (void)
{
    int state = chdir(command[1]);  /*the second argument is the path*/
    if(state == -1)
    {
        Assign_Err(current_process_pid,current_process_id,FAILED_CHANGE_DIR);
    }
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from builtin.c to perform env command to show all environmental variables 
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void env(void)
{
    for(unsigned int j=0 ; env_variables[j] != NULL ; j++)
    {
        printf("%s\n",env_variables[j]);
    }
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from builtin.c to show commands history
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void history_print(void)
{
    for(unsigned int k=0 ; k<history_num ; k++)
    {
        printf("%d\t%s\n",k,history[k]);
    }
}