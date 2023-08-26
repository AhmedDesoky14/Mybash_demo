/*     
*   Author: Ahmed Desoky
*   Date:   8/8/2023
*   Description:    bash backend functions source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include"exec_backend.h"
/*======================================================================GLOBAL VARIABES================================================================================*/
char* host_name;
char* user_name;
char* cwd;
unsigned int host_name_size;
unsigned int user_name_size;
unsigned int cwd_size;
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from exec.c to get status for prompt
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES:  This function assigns its errors to err_hndlr
************************************************************************************************************************************************/
void get_status(void)
{
    current_process_id = getpid();
    current_process_pid = getppid();
    current_user_id = getuid();
    int Usr_Err = gethostname(host_name,HOST_NAME_INITIAL_SIZE);   
    if(Usr_Err < 0)
    {
        Assign_Err(current_process_pid,current_process_id,GET_HOSTNAME_ERR);
    }
    user_name = getlogin(); /*this function returns a pointer to a statically allocated memory*/
    if(*user_name == '\0')
    {
        Assign_Err(current_process_pid,current_process_id,GET_USERNAME_ERR);
    }
    cwd = get_current_dir_name();
    if(*cwd == '\0')
    {
        Assign_Err(current_process_pid,current_process_id,GET_CWD_ERR);
    }
    host_name_size = strlen(host_name);
    cwd_size = strlen(cwd);
    host_name = (char*)realloc(host_name,(host_name_size+1)*sizeof(char));
    cwd = (char*)realloc(cwd,(cwd_size+1)*sizeof(char));
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from exec.c to get the PATH variable completly
    [INPUTS]:   pointer to character to hold the string of the PATH variable
    [OUTPUTS]:  NONE
    NOTES:  
************************************************************************************************************************************************/
void get_PATH_var(char* PATH_var)
{
    char PATH_var_str[6]="PATH=";
    unsigned int max_match = 0;
    unsigned int match = 0;
    for(unsigned int i=0 ; i<env_args_count ; i++)
    {
        for(unsigned int j=0 ; PATH_var_str[j]!='\0' ; j++)
        {
            
            if(env_variables[i][j] == PATH_var_str[j])
            {
                match++;
            }
        }
        if(match > max_match)
        {
            max_match = match;
            strcpy(PATH_var,env_variables[i]);
        }
        match = 0;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from exec.c to get the count of paths
    [INPUTS]:   pointer to character to hold the PATH variable
    [OUTPUTS]:  unsigned int to return number of paths
    NOTES:  
************************************************************************************************************************************************/
unsigned int count_paths(char* PATH_var)
{
    unsigned int paths_count = 0;
    for(unsigned int k=0 ; PATH_var[k]!='\0' ; k++)
    {
        if(PATH_var[k] == ':')
        {
            paths_count++;
        }
    }
    paths_count++;
    return paths_count;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from exec.c to tokenize the paths into many strings
    [INPUTS]:   pointer to char to send the single path, array of pointer to characters to hold the tokenized strings
    [OUTPUTS]:  NONE
    NOTES:  
************************************************************************************************************************************************/
void Exec_Paths_tokenizer(char* PATH_var,char** Exec_Paths)
{
    char* token;
    unsigned int count = 0;
    char PATH_var_dup[PATH_VAR_MAX_SIZE];
    strcpy(PATH_var_dup,PATH_var);
    token = strtok(PATH_var_dup, ":");
  	do
   	{

		Exec_Paths[count] = token;
 		count++;
   	}
   	while (token = strtok(NULL, ":"));
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   This is the function which is called from exec.c to search in the paths for the exe file
    [INPUTS]:   pointer to char to send the single path to search in it
    [OUTPUTS]:  integer indicating success or failure
    NOTES:  
************************************************************************************************************************************************/
int Exec_Seeker(char* Path)
{
    char* path = Path;
    int command_match = 0;
    DIR* dir_ectory = opendir(path);
    if(dir_ectory == NULL)
    {
        Assign_Err(current_process_pid,current_process_id,FAILED_OPEN_DIR);
        return -1;
    }
    struct dirent* direct_content = readdir(dir_ectory);
    if(strcmp(command[0],direct_content->d_name) == 0)
    {
        char temp_var[100];
        strcpy(temp_var,path);
        strcat(temp_var,"/");
        strcat(temp_var,command[0]);
        strcpy(exe,temp_var);
        if(closedir(dir_ectory)<0)
        {
           Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_DIR);
        }
        command_match = 1;
    }
    while ((direct_content = readdir(dir_ectory)))    
    {
        if(strcmp(command[0],direct_content->d_name) == 0)
        {
            char temp_var[100];
            strcpy(temp_var,path);
            strcat(temp_var,"/");
            strcat(temp_var,command[0]);
            strcpy(exe,temp_var);
            if(closedir(dir_ectory)<0)
            {
                Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_DIR);
            }
            command_match = 1;
        }
    }
    return command_match;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Special function only called by type command to get path for the command to know its type
    [INPUTS]:   pointer to char to send the single path to search in it
    [OUTPUTS]:  integer indicating success or failure
    NOTES: 
************************************************************************************************************************************************/
int special_path_seeker(char* Type_Path)
{   
    char* path = Type_Path;
    int command_match = 0;
    DIR* dir_ectory = opendir(path);
    if(dir_ectory == NULL)
    {
        Assign_Err(current_process_pid,current_process_id,FAILED_OPEN_DIR);
        return -1;
    }
    /*command[1] for the argument after type*/
    struct dirent* direct_content = readdir(dir_ectory);
    if(strcmp(command[1],direct_content->d_name) == 0)
    {
        char temp_var[100];
        strcpy(temp_var,path);
        strcat(temp_var,"/");
        strcat(temp_var,command[1]);
        strcpy(exe,temp_var);
        if(closedir(dir_ectory)<0)
        {
           Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_DIR);
        }
        command_match = 1;
    }
    while ((direct_content = readdir(dir_ectory)))    
    {
        if(strcmp(command[1],direct_content->d_name) == 0)
        {
            char temp_var[100];
            strcpy(temp_var,path);
            strcat(temp_var,"/");
            strcat(temp_var,command[1]);
            strcpy(exe,temp_var);
            if(closedir(dir_ectory)<0)
            {
                Assign_Err(current_process_pid,current_process_id,FAILED_CLOSE_DIR);
            }
            command_match = 1;
        }
    }
    return command_match;
}