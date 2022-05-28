#include "process.h"
#include "test_functions.h"
#include "kernel.h"
#include "process_pool.h"
#include "test_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Kernel Coração de mãe, sempre cabe mais um processo (durante runtime)

void TestProcessPoolFunctions(void);
void CreateProcesses(process_pool_t* pool);
void ProcessManagedByTime(void);

int main(void)
{
    //TestProcessPoolFunctions();
    ProcessManagedByTime();

    //Kernel_Loop();

    return 0;
}


void ProcessManagedByTime(void)
{
    kernel_t kernel;

    Kernel_Init(&kernel);

    CreateProcesses(&kernel.pool);

    //printf("pool size: %d\n", kernel.pool.current_size);

    Kernel_Loop(&kernel);
}

void CreateProcesses(process_pool_t* pool)
{
    process_t process;

    printf("Creating Processes\n");

    {
        process.TempoExec = 100;
        process.Prioridade = 1;
        process.ExecutionFunction = PrintMessageA;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        process.TempoExec = 200;
        process.Prioridade = 3;
        process.ExecutionFunction = PrintMessageB;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        process.TempoExec = 200;
        process.Prioridade = 3;
        process.ExecutionFunction = PrintMessageC;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    //printf("pool size: %d\n", pool->current_size);

    printf("Processes Created\n");
}

void TestProcessPoolFunctions(void)
{
    process_pool_t pool;

    Pool_Init(&pool);

    process_t proc;
    char proc_name[] = "A Proc";

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 0);

    proc_name[0] = 'B';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 0);

    proc_name[0] = 'C';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 0);

    proc_name[0] = 'D';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, pool.current_size);


    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    proc_name[0] = 'E';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 4);    

    printf("-----------\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_SwapNodeOrder(&pool, 0, 2);

    printf("----Swapped 0 and 4\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }


    Pool_RemoveEllementByIndex(&pool, 0);

    printf("-----Remove 0\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_RemoveEllementByIndex(&pool, pool.current_size);

    printf("-----Remove last\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_RemoveEllementByIndex(&pool, 1);

    printf("-----Remove 1\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_Clear(&pool);
    printf("Pool cleared\n");
}