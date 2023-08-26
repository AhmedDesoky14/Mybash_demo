/*     
*   Author: Ahmed Desoky
*   Date:   14/8/2023
*   Description:    Bash source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"parser.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   This is the function to retrieve the local variables
    [INPUTS]:   NONE
    [OUTPUTS]:  integer indicating success or failure of the function
    NOTES: This function uses, search_in_env, search_in_local and remove_char functions from parser_backend files
************************************************************************************************************************************************/
int var_retrieve_parser(void)
{
    int retrieve_state = 0;
    if(command[0][0] == '$')
    {
        remove_char(command[0],'$');
        char* temp_ptr = (char*)malloc(VAR_MAX_SIZE*sizeof(char));
        retrieve_state = search_in_env(command[0],temp_ptr);
        if(retrieve_state == 1)
        {
            for(unsigned int l=0 ;temp_ptr[l] != '\0' ; l++)
            {
                if(temp_ptr[l] == '=')
                {
                    strcpy(exe,temp_ptr+l+1);
                    free(temp_ptr);
                    return 1;
                }
            }
        }
        else
        {
            retrieve_state = search_in_local(command[0],temp_ptr);
            if(retrieve_state == 1)
            {
                for(unsigned int l=0 ;temp_ptr[l] != '\0' ; l++)
                {
                    if(temp_ptr[l] == '=')
                    {
                        strcpy(exe,temp_ptr+l+1);
                        free(temp_ptr);
                        return 1;
                    }
                }
            }
            else
            {
                free(temp_ptr);
                return -1; /*not found, do nothing*/
            }
        }
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function to assign new environmental variables
    [INPUTS]:   NONE
    [OUTPUTS]:  integer indicating success or failure of the function
    NOTES: This function uses, search_in_env_for_location and search_in_local_for_location functions from parser_backend files
************************************************************************************************************************************************/
int Assign_env_variables_parser(void)
{
    /*work for env variables*/
    int assign_state = 0;
    unsigned int location = 0;  
    for(unsigned int j=0 ; command[j] != NULL ; j++)
    {
        if(strcmp(command[j],"export") == 0)
        {
            for(unsigned int i=j+1 ; command[i]!= NULL ; i++)
            {
                unsigned int k = 0;
                while(command[i][k] != '\0')
                {
                    if(command[i][k] == '=')
                    {
                        if(command[i][k+1] == '=')  /*corner case error*/
                            return 0;
                        assign_state = 1; /*export and assign command found*/
                        int loc_found = search_in_env_for_location(command[i],&location);
                        if(loc_found == 1)
                        {
                            strcpy(env_variables[location],command[i]);
                        }
                        else
                        {
                            env_args_count++;
                            /*reallocate the array of pointers*/
                            env_variables = (char**)realloc(env_variables,(env_args_count+1)*sizeof(char*));
                            /*allocate memory for the string and make the last pointer in the array points to it*/
                            char* temp_var = (char*)malloc((strlen(command[i])+1)*sizeof(char));
                            env_variables[env_args_count-1] = temp_var;
                            strcpy(env_variables[env_args_count-1],command[i]);
                            /*closing the end of the array by pointing to*/
                            env_variables[env_args_count] = NULL;
                        }
                        break;
                    }
                    k++;
                }
                /*if '=' sign is not found*/ /*this section must be tested - 1:48 AM 16/8/2023*/
                {
                    /*search for the variable in the local variables*/
                    char* temp_ptr = (char*)malloc(VAR_MAX_SIZE*sizeof(char));
                    int decision = search_in_local(command[i],temp_ptr);
                    if(decision == 1)
                    {
                        assign_state = 1; /*export and assign command found*/
                        int loc_found = search_in_env_for_location(temp_ptr,&location);
                        if(loc_found == 1)
                        {
                            strcpy(env_variables[location],temp_ptr);
                        }
                        else
                        {
                            env_args_count++;
                            /*reallocate the array of pointers*/
                            env_variables = (char**)realloc(env_variables,(env_args_count+1)*sizeof(char*));
                            /*allocate memory for the string and make the last pointer in the array points to it*/
                            char* temp_var = (char*)malloc((strlen(command[i])+1)*sizeof(char));
                            env_variables[env_args_count-1] = temp_var;
                            strcpy(env_variables[env_args_count-1],temp_ptr);
                            env_variables[env_args_count] = NULL;
                        }
                    }
                    else
                    {
                        /*do nothing*/
                    }
                    free(temp_ptr);
                }
            }
        return assign_state;   /*1: means env variable assigned, 0: as it is no env variables assigned*/
        }
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function to assign new local variables
    [INPUTS]:   NONE
    [OUTPUTS]:  integer indicating success or failure of the function
    NOTES: This function uses, search_in_local_for_location functions from parser_backend files
************************************************************************************************************************************************/
int Assign_variables_parser(void)
{
    int assign_state = 0;
    unsigned int location = 0;  
    for(unsigned int i=0 ; command[i]!= NULL ; i++)
    {
        unsigned int k = 0;
        while(command[i][k] != '\0')
        {
            if(command[i][k] == '=')
            {
                if(command[i][k+1] == '=')  /*corner case error*/
                    return 0;
                assign_state = 1;    /*assign command found*/
                int loc_found;
                if(var_args_count > 1)
                {
                    loc_found = search_in_local_for_location(command[i],&location);
                }
                
                if(loc_found == 1)
                {
                    strcpy(variables[location],command[i]);
                }
                else
                {
                    var_args_count++;
                    /*reallocate the array of pointers*/
                    variables = (char**)realloc(variables,(var_args_count+1+100)*sizeof(char*)); /*+100 safe factor if the variable extended*/
                    /*allocate memory for the string and make the last pointer in the array points to it*/
                    char* temp_var = (char*)malloc((strlen(command[i])+1)*sizeof(char));
                    variables[var_args_count-1] = temp_var;
                    strcpy(variables[var_args_count-1],command[i]);
                    /*closing the end of the array by pointing to NULL*/
                    variables[var_args_count] = NULL;
                }
                break;
            }
            k++;
        }
    }
    return assign_state;   /*1: means env variable assigned, 0: as it is no env variables assigned*/
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

