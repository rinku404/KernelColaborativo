#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Process_SetName(process_t* process, char* name, int name_len)
{
    process->NomeProcesso = malloc(sizeof(char)*name_len);

    strcpy(process->NomeProcesso, name);
}

void Process_PrintName(process_t* process)
{
    printf("Process Name: %s\n", process->NomeProcesso);
}

void Process_SetMemory(process_t* process, int memory_data)
{
    process->MemoriaAloc = memory_data;    
}

void Process_PrintMemory(process_t* process)
{
    printf("Process Memory: %d\n", process->MemoriaAloc);
}

void Process_SetExecTime(process_t* process, float execution_time)
{
    process->TempoExec = execution_time;
}

void Process_PrintExecTime(process_t* process)
{
    printf("Process Execution Time: %.2f\n", process->TempoExec);
}

void Process_SetExecutionClass(process_t* process, process_execution_class_t* process_execution_class)
{
    process->process_execution_class = *process_execution_class;
}

void Process_PrintExecutionClass(process_t* process)
{
    switch (process->process_execution_class)
    {
    case REPEAT:
        
        printf("ProcessExecutionClass: \"Repeat\"\n");

        break;
    case ONCE:

        printf("ProcessExecutionClass: \"Once\"\n");

        break;
    
    default:
        break;
    }
}