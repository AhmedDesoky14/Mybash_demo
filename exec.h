/*     
*   Author: Ahmed Desoky
*   Date:   12/8/2023
*   Description:    execution header file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include<stdlib.h>
#include"exec_backend.h"
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function Descriptions in .c file*/
void Allocate_Memory(void);
void Free_Memory(void);
void Shell_Init(void);
void Shell_Deinit(void);
void Prompt(void);
int get_command(void);
int exe_path(void);
void add_history(void);