/*     
*   Author: Ahmed Desoky
*   Date:   12/8/2023
*   Description:    execution source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"exec.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   Function used by main directly to allocate needed memory
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Allocate_Memory(void)
{
    host_name = (char*)malloc(HOST_NAME_INITIAL_SIZE*sizeof(char));
    cwd = (char*)malloc(CWD_INITIAL_SIZE*sizeof(char));
    inputstring = malloc(INPUT_MAX_SIZE * sizeof(char*));
    command = (char**)malloc(COMMAND_MAX_SIZE*sizeof(char*));
    exe = (char*)malloc(COMMAND_FIRST_ARG_MAX_SIZE*sizeof(char));
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function used by main directly to free memory after every execution
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Free_Memory(void)
{
    free(host_name);
    free(inputstring);
    free(command);
    free(exe);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function used by main directly to Intiate the Shell
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Shell_Init(void)
{
    env_args_count = 0;
    /*Counting number of env varibles in environ*/
    while(environ[env_args_count] != NULL)
    {
        env_args_count++;
    }
    /*+1 to make space for the ending NULL*/
    env_variables = (char**)malloc((env_args_count+1)*sizeof(char*));   /* Allocating Dynamically pointer to pointers of characters for command*/
    for(unsigned int i=0 ; i<env_args_count ; i++)
    {
        env_variables[i] = environ[i];
    }
    /**/
    /*Note: NULL needs to be added at the end*/
    env_variables[env_args_count] = NULL;
    variables = (char**)malloc(sizeof(char*));
    variables[0] = NULL;
    var_args_count = 0;
    /*Allocate memory for history commands*/
    history = (char**)malloc(1*sizeof(char*));  /*Initial Value is 1*/
    history[0] = NULL;  /*Initially by NULL*/
    history_num = 0;
    /*Setting error log file location*/
    Err_Dir = malloc(CWD_INITIAL_SIZE*sizeof(char));
    Err_Dir = getcwd(Err_Dir,CWD_INITIAL_SIZE);
    strcat(Err_Dir,"/Err_Hist.txt");
}
/***********************************************************************************************************************************************
    Function Description:   Function used by main to add the command into history
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void add_history(void)
{
    history_num++;
    history = (char**)realloc(history,(history_num+1)*sizeof(char*));
    char* allocated_string = (char*)malloc(strlen(inputstring)*sizeof(char));
    strcpy(allocated_string,inputstring);
    history[history_num-1] = allocated_string;
    history[history_num] = NULL;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function used by main directly to Deintiate the Shell
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Shell_Deinit(void)
{
    free(cwd);      /*For changing directory*/
    free(history);  /*for history of commands*/
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function used by main directly to show prompt
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Prompt(void)
{
    get_status();
    printf("\033[1;32m%s@%s\033[1;0m:\033[1;34m~%s\033[1;0m$ ",user_name,host_name,cwd);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function used by main to get command and tokenize it
    [INPUTS]:   NONE
    [OUTPUTS]:  integer indicating success or failure
    NOTES: 
************************************************************************************************************************************************/
int get_command(void)
{
    fgets(inputstring, INPUT_MAX_SIZE, stdin);
    inputstring[strlen(inputstring) - 1] = 0; /* Putting Null instead of \n in last element */
    if(strlen(inputstring) == 0)    /*check if the input string is empty or not*/
    {
        return 0;
    }
    add_history(); 
    char* token;
    unsigned int count = 0;
    token = strtok(inputstring, " ");
  	do
   	{
		command[count] = token;
 		count++;
   	}
   	while (token = strtok(NULL, " "));
    command_args_count = count;
    /*Note: tokenizer doesn't add NULL at the end*/
    command[command_args_count] = NULL;
    /*+1 to make space for the ending NULL*/
    command = (char**)realloc(command,(command_args_count+1)*sizeof(char*));
    return 1;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function used by main to get the correct and the final path of the program for execution
    [INPUTS]:   NONE
    [OUTPUTS]:  integer indicating success or failure
    NOTES:  This function call get_PATH_var, count_paths, and Exec_Paths_tokenizer functions from exec_backend.c file
************************************************************************************************************************************************/
int exe_path(void)
{
    int command_match = 0;
    char PATH_var[PATH_VAR_MAX_SIZE];
    get_PATH_var(PATH_var);
    unsigned int Paths_count = count_paths(PATH_var);
    char** Exec_Paths = (char**)malloc((Paths_count+1)*sizeof(char*));
    Exec_Paths_tokenizer(PATH_var,Exec_Paths);
    for(unsigned int n=0 ; n<Paths_count ; n++)
    {
        command_match = Exec_Seeker(Exec_Paths[n]);
        if(command_match == 1)
            break;
    }
    free(Exec_Paths);
    if(command_match == 1)
    {
        return 1;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
