/*     
*   Author: Ahmed Desoky
*   Date:   14/8/2023
*   Description:    pasrer backend functions source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"parser_backend.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from parser.c to search for environ variables
    [INPUTS]:   pointer to char for variable needed to be found, pointer to char to hold the variable to make operations on it
    [OUTPUTS]:  interger to indicate if failed or succeeded
    NOTES:
************************************************************************************************************************************************/
int search_in_env(char* input_variable,char* env_variable_found)
{
    unsigned int max_match = 0;
    unsigned int match = 0;
    for(unsigned int j=0 ; env_variables[j] != NULL ; j++)
    {
        for(unsigned int k=0 ; input_variable[k]!='\0' ; k++)
        {
            
            if(env_variables[j][k] == input_variable[k])
            {
                match++;
            }
        }
        if(match > max_match)
        {
            max_match = match;
            strcpy(env_variable_found,env_variables[j]);
        }
        match = 0;
    }
    if(max_match == strlen(input_variable))
    {
        return 1;   /*sucessfully found*/
    }
    else
    {
        return -1;  /*not found, so do nothing*/
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from parser.c to search for local variables
    [INPUTS]:   pointer to char for variable needed to be found, pointer to char to hold the variable to make operations on it
    [OUTPUTS]:  interger to indicate if failed or succeeded
    NOTES:
************************************************************************************************************************************************/
int search_in_local(char* input_variable,char* local_variable_found)
{
    unsigned int max_match = 0;
    unsigned int match = 0;
    for(unsigned int j=0 ; variables[j] != NULL ; j++)
    {
        for(unsigned int k=0 ; input_variable[k]!='\0' ; k++)
        {
            
            if(variables[j][k] == input_variable[k])
            {
                match++;
            }
        }
        if(match > max_match)
        {
            max_match = match;
            strcpy(local_variable_found,variables[j]);
        }
        match = 0;
    }
    if(max_match == strlen(input_variable))
    {
        return 1;   /*sucessfully found*/
    }
    else
    {
        return -1;  /*not found, so do nothing*/
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from parser.c to remove character in a string
    [INPUTS]:   pointer to char for the string that needs the operation, char, the character needed to be removed
    [OUTPUTS]:  interger to indicate if failed or succeeded
    NOTES:
************************************************************************************************************************************************/
void remove_char(char* str,char character)
{
    int i,j;
    int len = strlen(str);
    for (i = j = 0; i < len; i++) 
    {
        if (str[i] != character) 
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from parser.c to search for environ variables, its location
    [INPUTS]:   pointer to char for variable needed to be found, pointer to int to pass the location of the variable by address
    [OUTPUTS]:  interger to indicate if failed or succeeded
    NOTES:
************************************************************************************************************************************************/
int search_in_env_for_location(char* input_variable,int* location)
{
    unsigned int max_match = 0;
    unsigned int match = 0;
    int found = 0;
    for(unsigned int j=0 ; env_variables[j] != NULL ; j++)
    {
        for(unsigned int k=0 ; input_variable[k]!='\0' ; k++)
        {
            
            if(env_variables[j][k] == input_variable[k])
            {
                match++;
            }
        }
        if(match > max_match)
        {
            max_match = match;
            *location = j;
            found = 1;
        }
        match = 0;
    }
    for(unsigned int cmp = 0 ; env_variables[*location][cmp] != '=' ; cmp++)
    {
        if(env_variables[*location][cmp] != input_variable[cmp])
        {
            found = 0;
            break;
        }
    }
    return found;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from parser.c to search for local variables, its location
    [INPUTS]:   pointer to char for variable needed to be found, pointer to int to pass the location of the variable by address
    [OUTPUTS]:  interger to indicate if failed or succeeded
    NOTES:
************************************************************************************************************************************************/
int search_in_local_for_location(char* input_variable,int* location)
{
    unsigned int max_match = 0;
    unsigned int match = 0;
    int found = 0;
    for(unsigned int j=0 ; variables[j] != NULL ; j++)
    {
        for(unsigned int k=0 ; input_variable[k]!='\0' ; k++)
        {
            
            if(variables[j][k] == input_variable[k])
            {
                match++;
            }
        }
        if(match > max_match)
        {
            max_match = match;
            *location = j;
            found = 1;
        }
        match = 0;
    }
    for(unsigned int cmp = 0 ; variables[*location][cmp] != '=' ; cmp++)
    {
            if(variables[*location][cmp] != input_variable[cmp])
            {
                found = 0;
                break;
            }
    }
    return found;
}
