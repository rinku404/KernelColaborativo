#ifndef PROCESS_H
#define PROCESS_H


typedef enum
{
    REPEAT,
    ONCE
}process_execution_class_t;

typedef void (*ExecutionFunction_t)(void);

struct 
{
    char*                       NomeProcesso;
    int                         MemoriaAloc;
    float                       TempoExec;
    int                         Prioridade;
    int                         start;
    process_execution_class_t   process_execution_class;
    ExecutionFunction_t         ExecutionFunction;

} typedef process_t;

void Process_SetName(process_t* process, char* name, int name_len);
void Process_PrintName(process_t* process);
void Process_SetMemory(process_t* process, int memory_data);
void Process_PrintMemory(process_t* process);
void Process_SetExecTime(process_t* process, float execution_time);
void Process_PrintExecTime(process_t* process);
void Process_RegisterExecutionFunction(process_t* process, ExecutionFunction_t ExecutionFunction);
void Process_SetExecutionClass(process_t* process, process_execution_class_t* process_execution_class);
void Process_PrintExecutionClass(process_t* process);
void Process_SetPriority(process_t* process, int priority);
void Process_PrintPriority(process_t* process);
void Process_FreeMemory(process_t* process);

#endif